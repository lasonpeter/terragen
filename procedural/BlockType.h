//
// Created by lasek on 05.04.25.
//

#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H


enum class BlockType {
    AIR,
    GRASS,
    DIRT,
    STONE
};

inline const char *to_string(BlockType e) {
    switch (e) {
        case BlockType::AIR: return "AIR";
        case BlockType::GRASS: return "GRASS";
        case BlockType::DIRT: return "DIRT";
        case BlockType::STONE: return "STONE";
        default: return "unknown";
    }
}
#endif //BLOCKTYPE_H
