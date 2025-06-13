//
// Created by Dorian on 12.06.2025.
//

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define ASIO_NO_WINDOWS_H
#define NOUSER
#define NOGDI
#define NODRAWTEXT
#define NOMCX
#define NOSHOWWINDOW
#define NOCLOSEWINDOW
#define VC_EXTRALEAN

#ifndef NETCODE_H
#define NETCODE_H
#include <asio.hpp>

#include "ProtoClient.h"
#include "generated/ChunkTransmitModel.pb.h"


enum class BlockType : uint8_t;
class Chunk;

class Netcode {



public:

    asio::io_context io_context;

    ProtoClient client;

    std::vector <Chunk*> chunks;

    Netcode();
    ~Netcode() = default;



    void connect(const std::string& host, const int& port) {
        client.connectTcp(host, port);
    }


    void Login();

    void Receiver();

    void sendMessageTcp(const google::protobuf::Message& message, terragen::MessageType type) {
        client.sendMessageTcp(message, type);
    }

    void SendPosition(std::string username, float x, float y, float z, float rotationX);

    void SendBlockUpdate(int chunkx, int chunkz, int x, int y, int z, BlockType blockType);



};



#endif //NETCODE_H
