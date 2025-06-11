//
// Created by lasek on 05.04.25.
//

#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H


#include <cstdint>
#include "../data/textures/blocks/blocks.h"

struct AtlasTexture{
    float positionX;
    float positionY;
    float sourceWidth;
    float sourceHeight;
};

enum class BlockType : uint8_t{
    AIR =0,
    GRASS =1,
    DIRT =2,
    STONE =3,
    WOOD =4,
    LEAVES =5,
};


inline const char *to_string(BlockType e) {
    switch (e) {
        case BlockType::AIR: return "AIR";
        case BlockType::GRASS: return "GRASS";
        case BlockType::DIRT: return "DIRT";
        case BlockType::STONE: return "STONE";
        case BlockType::WOOD: return "WOOD";
        case BlockType::LEAVES: return "LEAVES";
        default: return "unknown";
    }
}

inline const bool is_transparent(BlockType e) {
    switch (e) {
        case BlockType::AIR: return true;
        case BlockType::GRASS: return false;
        case BlockType::DIRT: return false;
        case BlockType::STONE: return false;
        case BlockType::WOOD: return false;
        case BlockType::LEAVES: return false;
        default: return true;
    }
}

inline const Vector4 texture_coords(BlockType e){
    switch (e) {
        case BlockType::DIRT:
            return Vector4{
                static_cast<float>(rtpDescAtlas[0].positionX),
                static_cast<float>(rtpDescAtlas[0].positionY),
                static_cast<float>(rtpDescAtlas[0].sourceWidth),
                static_cast<float>(rtpDescAtlas[0].sourceHeight)
            };
        case BlockType::STONE:
            return Vector4{
                static_cast<float>(rtpDescAtlas[1].positionX),
                static_cast<float>(rtpDescAtlas[1].positionY),
                static_cast<float>(rtpDescAtlas[1].sourceWidth),
                static_cast<float>(rtpDescAtlas[1].sourceHeight)
            };
        case BlockType::AIR:
            return Vector4{0.0f, 0.0f, 0.0f, 0.0f};
        case BlockType::GRASS:
            return Vector4{
                static_cast<float>(rtpDescAtlas[0].positionX),
                static_cast<float>(rtpDescAtlas[0].positionY),
                static_cast<float>(rtpDescAtlas[0].sourceWidth),
                static_cast<float>(rtpDescAtlas[0].sourceHeight)
            };
        default:
            return Vector4{0.0f, 0.0f, 0.0f, 0.0f};
    }
}

inline const AtlasTexture uv_coords(BlockType e){
    switch (e) {
        case BlockType::DIRT:
            return AtlasTexture{
                static_cast<float>(rtpDescAtlas[0].positionX),
                static_cast<float>(rtpDescAtlas[0].positionY),
                static_cast<float>(rtpDescAtlas[0].sourceWidth),
                static_cast<float>(rtpDescAtlas[0].sourceHeight)
            };
        case BlockType::GRASS:
            return AtlasTexture{
                static_cast<float>(rtpDescAtlas[4].positionX),
                static_cast<float>(rtpDescAtlas[4].positionY),
                static_cast<float>(rtpDescAtlas[4].sourceWidth),
                static_cast<float>(rtpDescAtlas[4].sourceHeight)
            };
        case BlockType::STONE:
            return AtlasTexture{
                static_cast<float>(rtpDescAtlas[1].positionX),
                static_cast<float>(rtpDescAtlas[1].positionY),
                static_cast<float>(rtpDescAtlas[1].sourceWidth),
                static_cast<float>(rtpDescAtlas[1].sourceHeight)
            };
        case BlockType::AIR:
        default:
            return AtlasTexture{0.0f, 0.0f, 0.0f, 0.0f};
    }
}


#endif //BLOCKTYPE_H