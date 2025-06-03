#pragma once

#include <asio.hpp>
#include <google/protobuf/message.h>

// Wygenerowane pliki .pb.h (z Twoich .proto)
#include "EnvelopeModel.pb.h"
#include "LoginModel.pb.h"
#include "ChatMessageModel.pb.h"
#include "BlockUpdateModel.pb.h"
#include "PositionUpdateModel.pb.h"

#include <unordered_map>
#include <vector>
#include <deque>
#include <memory>
#include <functional>
#include <cstdint>

// Definiujemy alias na callback, który zwraca wskaźnik do zdeserializowanej wiadomości Protobuf
using MessageCallback = std::function<void(std::unique_ptr<google::protobuf::Message>)>;

class ProtoClient {
public:
    explicit ProtoClient(asio::io_context& io_context);

    // --- TCP ---
    /// Zainicjuj połączenie TCP do host:port
    void connectTcp(const std::string& host, unsigned short port);
    /// Rozpocznij asynchroniczne nasłuchiwanie TCP (wywoła onMessage dla każdej pełnej EnvelopeModel)
    void startReceiveTcp(MessageCallback onMessage);

    // --- UDP ---
    /// Rozpocznij asynchroniczne nasłuchiwanie UDP na danym porcie (wywoła onMessage dla każdej pełnej EnvelopeModel)
    void startReceiveUdp(unsigned short localPort, MessageCallback onMessage);

private:
    // --- Wspólne metody ---
    /// Próbuj sparsować bajty do EnvelopeModel
    bool parseEnvelope(const std::vector<uint8_t>& buf, terragen::EnvelopeModel& env);

    /// Na podstawie zawartości `env` tworzy i parsuje właściwy obiekt Protobuf (LoginModel, ChatMessageModel itd.)
    std::unique_ptr<google::protobuf::Message> dispatchPayload(const terragen::EnvelopeModel& env);

    // --- TCP ---
    /// Callback do odczytu nagłówka (4 bajty długości) z TCP
    void handleTcpReadHeader(const asio::error_code& ec, std::size_t bytes_transferred);
    /// Callback do odczytu ciała wiadomości (header + payload) z TCP
    void handleTcpReadBody(const asio::error_code& ec, std::size_t bytes_transferred);

    /// Socket TCP
    asio::ip::tcp::socket tcpSocket_;

    /// Ile bajtów ma „header” definiujący długość całej wiadomości (4 bajty w big-endianie)
    enum : std::size_t { HEADER_LENGTH = 4 };
    /// Zmienna pomocnicza do trzymania tej długości (w formacie sieciowym)
    uint32_t incomingMsgLen_;

    /// Bufor na bajty pochodzące z sieci (payload envelopu)
    std::vector<uint8_t> incomingBuffer_;

    /// W przypadku fragmentacji TCP (PocketCount > 1) – tymczasowe przechowywanie częściowych EnvelopeModel
    std::unordered_map<std::string, std::vector<terragen::EnvelopeModel>> incompleteTcp_;

    /// Przechowujemy callback, żeby w kolejnych wywołaniach mogło być do niego odwołanie
    MessageCallback tcpCallback_;

    // --- UDP ---
    /// Callback do odczytu pakietu UDP
    void handleUdpReceive(const asio::error_code& ec, std::size_t bytes_transferred);

    /// Socket UDP
    asio::ip::udp::socket udpSocket_;
    /// Endpoint nadawcy (do użytku, gdybyś chciał odsyłać odpowiedź)
    asio::ip::udp::endpoint udpSenderEndpoint_;
    /// Bufor na przychodzące dane UDP
    std::vector<uint8_t> udpBuffer_;
    /// Przechowujemy callback dla UDP
    MessageCallback udpCallback_;
};