#include "ProtoClient.h"
#include <iostream>

// ---------------------------------------------------------------------------------
//                KONSTRUKTOR I INICJALIZACJA SOCKETÓW
// ---------------------------------------------------------------------------------
ProtoClient::ProtoClient(asio::io_context& io_context)
  : tcpSocket_(io_context),
    udpSocket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
    incomingMsgLen_(0),
    udpBuffer_(1500) // standardowy bufor UDP (~MTU)
{
    // udpSocket_ został już wstępnie utworzony (0 = dowolny wolny port lokalny)
}

// ---------------------------------------------------------------------------------
//                              METODY TCP
// ---------------------------------------------------------------------------------
void ProtoClient::connectTcp(const std::string& host, unsigned short port) {
    // Resolver Asio używa io_context wbudowanego w tcpSocket_
    asio::ip::tcp::resolver resolver(tcpSocket_.get_executor());
    // Uzyskujemy listę endpointów odpowiadających "host:port"
    auto endpoints = resolver.resolve(host, std::to_string(port));

    // Blokujące połączenie (synchronne) – Asio zadba o próbę kilku endpointów
    asio::error_code ec;
    asio::connect(tcpSocket_, endpoints, ec);
    if (ec) {
        std::cerr << "[ProtoClient] Błąd przy połączeniu TCP: " << ec.message() << "\n";
    } else {
        std::cout << "[ProtoClient] Połączono TCP z " << host << ":" << port << "\n";
    }
}

void ProtoClient::startReceiveTcp(MessageCallback onMessage) {
    tcpCallback_ = std::move(onMessage);

    // Uruchamiamy asynchroniczny odczyt nagłówka (4 bajty = uint32_t długość)
    // Uwaga: w przychodzącym buforze trzymamy wartość w sieciowym porządku bajtów (big-endian).
    asio::async_read(
        tcpSocket_,
        asio::buffer(&incomingMsgLen_, HEADER_LENGTH),
        [this](const asio::error_code& ec, std::size_t bytes_transferred) {
            handleTcpReadHeader(ec, bytes_transferred);
        }
    );
}

void ProtoClient::handleTcpReadHeader(const asio::error_code& ec, std::size_t /*bytes_transferred*/) {
    if (ec) {
        std::cerr << "[ProtoClient] Błąd odczytu TCP nagłówka: " << ec.message() << "\n";
        return;
    }

    // Zamiana z big-endian (ntohl) na host-order
    uint32_t netlen = incomingMsgLen_;
    incomingMsgLen_ = ntohl(netlen);

    // Przygotuj bufor na dokładnie tyle bajtów
    incomingBuffer_.resize(incomingMsgLen_);

    // Teraz asynchronicznie czytamy całe ciało wiadomości (payload = serialized EnvelopeModel)
    asio::async_read(
        tcpSocket_,
        asio::buffer(incomingBuffer_),
        [this](const asio::error_code& ec2, std::size_t bytes_transferred2) {
            handleTcpReadBody(ec2, bytes_transferred2);
        }
    );
}

void ProtoClient::handleTcpReadBody(const asio::error_code& ec, std::size_t /*bytes_transferred*/) {
    if (ec) {
        std::cerr << "[ProtoClient] Błąd odczytu TCP ciała: " << ec.message() << "\n";
        return;
    }

    // Mamy już cały bajtowy bufor odpowiadający jednemu EnvelopeModel (lub jego fragmentowi).
    terragen::EnvelopeModel env;
    if (!parseEnvelope(incomingBuffer_, env)) {
        std::cerr << "[ProtoClient] Nie udało się zdeserializować EnvelopeModel\n";
    } else {
        // Sprawdź, czy jest fragmentacja (PocketCount > 1)
        if (env.pocketscount() > 1) {
            auto& vec = incompleteTcp_[env.id()];
            if (vec.empty()) {
                // Jeśli jeszcze nic nie ma, inicjuj vector<EnvelopeModel> o rozmiarze pocketscount()
                vec.resize(env.pocketscount());
            }
            // Wstaw pobrany fragment pod indeks env.pocketid()
            vec[env.pocketid()] = env;

            // Sprawdź, czy mamy wszystkie części
            bool complete = true;
            for (auto& chunkEnv : vec) {
                if (chunkEnv.id().empty()) {
                    complete = false;
                    break;
                }
            }

            if (complete) {
                // Scal payloady w jeden wektor bajtów
                std::vector<uint8_t> fullPayload;
                for (auto& chunkEnv : vec) {
                    const auto& part = chunkEnv.payload();
                    fullPayload.insert(fullPayload.end(),
                                       reinterpret_cast<const uint8_t*>(part.data()),
                                       reinterpret_cast<const uint8_t*>(part.data()) + part.size());
                }

                // Utwórz nowy EnvelopeModel ze scalonym payloadem
                terragen::EnvelopeModel merged;
                merged.set_id(env.id());
                merged.set_pocketid(0);
                merged.set_pocketscount(1);
                merged.set_type(env.type());
                merged.set_payload(std::string(reinterpret_cast<const char*>(fullPayload.data()), fullPayload.size()));

                // Przekaż dalej do deserializacji właściwego obiektu Protobuf
                auto messagePtr = dispatchPayload(merged);
                if (messagePtr && tcpCallback_) {
                    tcpCallback_(std::move(messagePtr));
                }

                // Usuń wpis z incompleteTcp_
                incompleteTcp_.erase(env.id());
            }
        }
        else {
            // Brak fragmentacji – od razu deserializuj payload
            auto messagePtr = dispatchPayload(env);
            if (messagePtr && tcpCallback_) {
                tcpCallback_(std::move(messagePtr));
            }
        }
    }

    // Ponownie zaczynamy odczyt kolejnej wiadomości:
    startReceiveTcp(tcpCallback_);
}

void ProtoClient::sendTcp(const terragen::EnvelopeModel& env) {
    std::string data;
    if (!env.SerializeToString(&data)) {
        std::cerr << "[ProtoClient] Nie udało się zserializować EnvelopeModel (TCP)\n";
        return;
    }

    asio::error_code ec;
    asio::write(tcpSocket_, asio::buffer(data), ec);

    if (ec) {
        std::cerr << "[ProtoClient] Błąd wysyłania TCP: " << ec.message() << "\n";
    }
}

// ---------------------------------------------------------------------------------
//                              METODY UDP
// ---------------------------------------------------------------------------------
void ProtoClient::startReceiveUdp(unsigned short localPort, MessageCallback onMessage) {
    // Zamknij (jeśli było otwarte) i otwórz na nowo, tym razem bind na konkretny port
    asio::error_code ec_open;
    udpSocket_.close(ec_open);
    udpSocket_.open(asio::ip::udp::v4(), ec_open);

    asio::error_code ec_bind;
    udpSocket_.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), localPort), ec_bind);
    if (ec_bind) {
        std::cerr << "[ProtoClient] Nie udało się zbindować UDP na porcie " << localPort
                  << ": " << ec_bind.message() << "\n";
        return;
    }

    udpCallback_ = std::move(onMessage);

    // Uruchamiamy asynchroniczny odbiór
    udpSocket_.async_receive_from(
        asio::buffer(udpBuffer_),
        udpSenderEndpoint_,
        [this](const asio::error_code& ec2, std::size_t bytes_recvd) {
            handleUdpReceive(ec2, bytes_recvd);
        }
    );
}

void ProtoClient::handleUdpReceive(const asio::error_code& ec, std::size_t bytes_recvd) {
    if (!ec) {
        // Skopiuj odebrane bajty do std::vector<uint8_t>
        std::vector<uint8_t> data(udpBuffer_.begin(), udpBuffer_.begin() + bytes_recvd);

        terragen::EnvelopeModel env;
        if (!parseEnvelope(data, env)) {
            std::cerr << "[ProtoClient] Błąd deserializacji UDP EnvelopeModel\n";
        } else {
            // Jeśli fragmentacja (pocketscount > 1) – odrzuć (nie obsługujemy UDP fragmentacji)
            if (env.pocketscount() > 1) {
                std::cerr << "[ProtoClient] Odrzucono fragment UDP (nieobsługiwane)\n";
            } else {
                auto messagePtr = dispatchPayload(env);
                if (messagePtr && udpCallback_) {
                    udpCallback_(std::move(messagePtr));
                }
            }
        }

        // Nasłuchuj dalej
        startReceiveUdp(udpSocket_.local_endpoint().port(), udpCallback_);
    }
    else {
        std::cerr << "[ProtoClient] Błąd przy odbiorze UDP: " << ec.message() << "\n";
    }
}

// ---------------------------------------------------------------------------------
//                           PARSE I DISPATCH
// ---------------------------------------------------------------------------------
bool ProtoClient::parseEnvelope(const std::vector<uint8_t>& buf, terragen::EnvelopeModel& env) {
    // ParseFromArray zwraca false, jeśli bufor nie jest poprawnym serialized EnvelopeModel
    return env.ParseFromArray(buf.data(), static_cast<int>(buf.size()));
}

std::unique_ptr<google::protobuf::Message> ProtoClient::dispatchPayload(const terragen::EnvelopeModel& env) {
    const auto& payload = env.payload(); // std::string z surowymi bajtami

    /*
    switch (env.type()) {
        case terragen::MessageType::LOGIN: {
            auto msg = std::make_unique<terragen::LoginModel>();
            if (msg->ParseFromArray(payload.data(), static_cast<int>(payload.size()))) {
                return msg;
            }
            break;
        }
        case terragen::MessageType::CHAT: {
            auto msg = std::make_unique<terragen::ChatMessageModel>();
            if (msg->ParseFromArray(payload.data(), static_cast<int>(payload.size()))) {
                return msg;
            }
            break;
        }
        case terragen::MessageType::POSITION_UPDATE: {
            auto msg = std::make_unique<terragen::PositionUpdateModel>();
            if (msg->ParseFromArray(payload.data(), static_cast<int>(payload.size()))) {
                return msg;
            }
            break;
        }
        case terragen::MessageType::BLOCK_UPDATE: {
            auto msg = std::make_unique<terragen::BlockUpdateModel>();
            if (msg->ParseFromArray(payload.data(), static_cast<int>(payload.size()))) {
                return msg;
            }
            break;
        }
        // Dodaj tutaj inne typy wiadomości, jeżeli je masz (LOGIN_RESPONSE, DISCONNECT, itd.)
        default:
            std::cerr << "[ProtoClient] Nieznany typ wiadomości: " << env.type() << "\n";
            break;
    }*/
    return nullptr;
}