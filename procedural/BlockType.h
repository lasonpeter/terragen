//
// Created by lasek on 05.04.25.
//

#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H


#include <cstdint>

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
        case BlockType::LEAVES: return true;
        default: return true;
    }
}
#endif //BLOCKTYPE_H
