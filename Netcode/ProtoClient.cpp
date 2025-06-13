#include "ProtoClient.h"
#include <iostream>

#include "generated/ChunkTransmitModel.pb.h"


ProtoClient::ProtoClient(asio::io_context& io_context)
  : tcpSocket_(io_context),
    udpSocket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
    incomingMsgLen_(0),
    udpBuffer_(1500)
{

}

void ProtoClient::connectTcp(const std::string& host, unsigned short port) {

    asio::ip::tcp::resolver resolver(tcpSocket_.get_executor());

    auto endpoints = resolver.resolve(host, std::to_string(port));


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


    uint32_t netlen = incomingMsgLen_;
    incomingMsgLen_ = ntohl(netlen);


    incomingBuffer_.resize(incomingMsgLen_);


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


    terragen::EnvelopeModel env;
    if (!parseEnvelope(incomingBuffer_, env)) {
        std::cerr << "[ProtoClient] Nie udało się zdeserializować EnvelopeModel\n";
    } else {

        if (env.pocketscount() > 1) {
            auto& vec = incompleteTcp_[env.id()];
            if (vec.empty()) {

                vec.resize(env.pocketscount());
            }

            vec[env.pocketid()] = env;


            bool complete = true;
            for (auto& chunkEnv : vec) {
                if (chunkEnv.id().empty()) {
                    complete = false;
                    break;
                }
            }

            if (complete) {

                std::vector<uint8_t> fullPayload;
                for (auto& chunkEnv : vec) {
                    const auto& part = chunkEnv.payload();
                    fullPayload.insert(fullPayload.end(),
                                       reinterpret_cast<const uint8_t*>(part.data()),
                                       reinterpret_cast<const uint8_t*>(part.data()) + part.size());
                }


                terragen::EnvelopeModel merged;
                merged.set_id(env.id());
                merged.set_pocketid(0);
                merged.set_pocketscount(1);
                merged.set_type(env.type());
                merged.set_payload(std::string(reinterpret_cast<const char*>(fullPayload.data()), fullPayload.size()));


                auto messagePtr = dispatchPayload(merged);
                if (messagePtr && tcpCallback_) {
                    tcpCallback_(std::move(messagePtr));
                }


                incompleteTcp_.erase(env.id());
            }
        }
        else {

            auto messagePtr = dispatchPayload(env);
            if (messagePtr && tcpCallback_) {
                tcpCallback_(std::move(messagePtr));
            }
        }
    }


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

        std::vector<uint8_t> data(udpBuffer_.begin(), udpBuffer_.begin() + bytes_recvd);

        terragen::EnvelopeModel env;
        if (!parseEnvelope(data, env)) {
            std::cerr << "[ProtoClient] Błąd deserializacji UDP EnvelopeModel\n";
        } else {

            if (env.pocketscount() > 1) {
                std::cerr << "[ProtoClient] Odrzucono fragment UDP (nieobsługiwane)\n";
            } else {
                auto messagePtr = dispatchPayload(env);
                if (messagePtr && udpCallback_) {
                    udpCallback_(std::move(messagePtr));
                }
            }
        }


        startReceiveUdp(udpSocket_.local_endpoint().port(), udpCallback_);
    }
    else {
        std::cerr << "[ProtoClient] Błąd przy odbiorze UDP: " << ec.message() << "\n";
    }
}


bool ProtoClient::parseEnvelope(const std::vector<uint8_t>& buf, terragen::EnvelopeModel& env) {

    return env.ParseFromArray(buf.data(), static_cast<int>(buf.size()));
}

std::unique_ptr<google::protobuf::Message> ProtoClient::dispatchPayload(const terragen::EnvelopeModel& env) {
    const auto& payload = env.payload();
    switch (env.type())
    {
    case terragen::MessageType::CHUNK_TRANSMIT: {
            auto msg = std::make_unique<terragen::ChunkTransmitModel>();
            if (msg->ParseFromArray(payload.data(), static_cast<int>(payload.size()))) {
                return msg;
            }
            break;
        }
    }

    return nullptr;
}