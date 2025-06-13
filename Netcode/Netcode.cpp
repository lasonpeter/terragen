//
// Created by Dorian on 12.06.2025.
//

#include "Netcode.h"
#include <bitset>
#include <iostream>
#include <vector>

#include "../utilities/Mathf.h"
#include "../procedural/Block.h"
#include "../procedural/Chunk.h"
#include "raygui.h"
#include "raymath.h"
#include "generated/BlockUpdateBroadcastModel.pb.h"
#include "generated/BlockUpdateModel.pb.h"
#include "generated/LoginRespondModel.pb.h"
#include "generated/PositionUpdateBroadcastModel.pb.h"
#include "generated/PositionUpdateModel.pb.h"

enum class BlockType : uint8_t;
class Block;

Netcode::Netcode(): client(io_context)
{
}

void Netcode::Login()
{
    terragen::LoginModel loginModel;
    loginModel.set_username("Pixel");
    loginModel.set_version(1);
    loginModel.set_udpaddress("127.0.0.1");
    loginModel.set_udpport(7778);
    client.sendMessageTcp(loginModel, terragen::MessageType::LOGIN);
}

void Netcode::Receiver()
{
    client.startReceiveTcp([this](std::unique_ptr<google::protobuf::Message> msg) {
        if (auto login = dynamic_cast<terragen::LoginRespondModel*>(msg.get())) {
            std::cout<<"Connection status: "<<login->success()<<"\n";
            std::cout<<"UDP port: "<<login->udpport()<<"\n";
        }
        else if (auto chunk = dynamic_cast<terragen::ChunkTransmitModel*>(msg.get()))
        {
            auto bytes = chunk->data();

            auto chunkId = chunk->id();

            auto pos = chunkId.find('_');
            int x = std::stoi(chunkId.substr(0, pos));
            int z = std::stoi(chunkId.substr(pos + 1));

            Int2 chunkPos = {x, z};

            std::vector<uint8_t> data;
            for (unsigned char c: bytes)
            {
                data.push_back(static_cast<uint8_t>(c));
            }

            std::vector<Block> enums;
            for (uint8_t b : data)
            {
                enums.push_back(Block(static_cast<BlockType>(b)));
            }

            Chunk* chunka = new Chunk(chunkPos);

            std::copy(enums.begin(), enums.end(), chunka->blocks);

            chunks.push_back(chunka);
        }
        else if (auto chunk = dynamic_cast<terragen::BlockUpdateBroadcastModel*>(msg.get()))
        {
            auto bytes = chunk->data();

            auto chunkId = chunk->id();

            auto pos = chunkId.find('_');
            int x = std::stoi(chunkId.substr(0, pos));
            int z = std::stoi(chunkId.substr(pos + 1));

            Int2 chunkPos = {x, z};

            std::vector<uint8_t> data;
            for (unsigned char c: bytes)
            {
                data.push_back(static_cast<uint8_t>(c));
            }

            std::vector<Block> enums;
            for (uint8_t b : data)
            {
                enums.push_back(Block(static_cast<BlockType>(b)));
            }

            Chunk* chunka = new Chunk(chunkPos);

            std::copy(enums.begin(), enums.end(), chunka->blocks);


            //TODO: gotowy chunk "chunka" zaktualizowany, dodaj go do cache'a

        }
        else if (auto playerPos = dynamic_cast<terragen::PositionUpdateBroadcastModel*>(msg.get()))
        {
            //TODO: generate player mesh
            std::string username = playerPos->playername();

            Vector3 position = {
                playerPos->x(),
                playerPos->y(),
                playerPos->z()
            };

            float rotation = playerPos->rotationx();
        }
        else
        {
            std::cout<<"Unknown message received\n";
        }
    });
}

void Netcode::SendPosition(std::string username, float x, float y, float z, float rotationX)
{
    terragen::PositionUpdateModel positionUpdate;
    positionUpdate.set_username(username);
    positionUpdate.set_x(x);
    positionUpdate.set_y(y);
    positionUpdate.set_z(z);
    positionUpdate.set_rotationx(rotationX);

    sendMessageTcp(positionUpdate, terragen::MessageType::POSITION_UPDATE);
}

void Netcode::SendBlockUpdate(int chunkx, int chunkz, int x, int y, int z, BlockType blockType)
{
    terragen::BlockUpdateModel blockUpdate;
    blockUpdate.set_blockx(x);
    blockUpdate.set_blocky(y);
    blockUpdate.set_blockz(z);
    blockUpdate.set_blockid(static_cast<uint8_t>(blockType));
    blockUpdate.set_chunkx(chunkx);
    blockUpdate.set_chunkz(chunkz);

    sendMessageTcp(blockUpdate, terragen::MessageType::BLOCK_UPDATE);
}
