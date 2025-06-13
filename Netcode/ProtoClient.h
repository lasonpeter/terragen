#pragma once

#define _WIN32_WINNT 0x0601


#include <asio.hpp>
#include <../include/google/protobuf/message.h>

#include "generated/EnvelopeModel.pb.h"
#include "generated/LoginModel.pb.h"
//#include "ChatMessageModel.pb.h"
//#include "BlockUpdateModel.pb.h"
//#include "PositionUpdateModel.pb.h"

#include <unordered_map>
#include <vector>
#include <deque>
#include <memory>
#include <functional>


using MessageCallback = std::function<void(std::unique_ptr<google::protobuf::Message>)>;

class ProtoClient {
public:
    explicit ProtoClient(asio::io_context& io_context);

    // --- TCP ---
    void connectTcp(const std::string& host, unsigned short port);
    void startReceiveTcp(MessageCallback onMessage);

    // --- UDP ---
    void startReceiveUdp(unsigned short localPort, MessageCallback onMessage);

    template<typename T>
    void sendMessageTcp(const T& message, terragen::MessageType type) {
        std::string payload;
        if (!message.SerializeToString(&payload)) {
            std::cerr << "[ProtoClient] Nie udało się zserializować wiadomości wewnętrznej\n";
            return;
        }

        terragen::EnvelopeModel envelope;
        envelope.set_id("msg_" + std::to_string(rand()));
        envelope.set_pocketid(0);
        envelope.set_pocketscount(1);
        envelope.set_type(type);
        envelope.set_payload(payload);

        sendTcp(envelope);
    }

    template<typename T>
    void sendMessageUdp(const T& message, terragen::MessageType type, const std::string& host, unsigned short port) {
        std::string payload;
        if (!message.SerializeToString(&payload)) {
            std::cerr << "[ProtoClient] Nie udało się zserializować wiadomości wewnętrznej (UDP)\n";
            return;
        }

        terragen::EnvelopeModel envelope;
        envelope.set_id("msg_" + std::to_string(rand()));
        envelope.set_pocketid(0);
        envelope.set_pocketscount(1);
        envelope.set_type(type);
        envelope.set_payload(payload);

        //sendUdp(envelope, host, port);
    }

private:
    // --- Wspólne metody ---
    bool parseEnvelope(const std::vector<uint8_t>& buf, terragen::EnvelopeModel& env);

    std::unique_ptr<google::protobuf::Message> dispatchPayload(const terragen::EnvelopeModel& env);

    // --- TCP ---
    void handleTcpReadHeader(const asio::error_code& ec, std::size_t bytes_transferred);

    void handleTcpReadBody(const asio::error_code& ec, std::size_t bytes_transferred);

    /// Socket TCP
    asio::ip::tcp::socket tcpSocket_;


    enum : std::size_t { HEADER_LENGTH = 4 };

    uint32_t incomingMsgLen_;


    std::vector<uint8_t> incomingBuffer_;


    std::unordered_map<std::string, std::vector<terragen::EnvelopeModel>> incompleteTcp_;


    MessageCallback tcpCallback_;

    // --- UDP ---

    void handleUdpReceive(const asio::error_code& ec, std::size_t bytes_transferred);


    asio::ip::udp::socket udpSocket_;

    asio::ip::udp::endpoint udpSenderEndpoint_;

    std::vector<uint8_t> udpBuffer_;

    MessageCallback udpCallback_;

    void sendTcp(const terragen::EnvelopeModel& env);



};