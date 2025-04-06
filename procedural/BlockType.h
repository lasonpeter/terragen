//
// Created by lasek on 05.04.25.
//

#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H


enum BlockType {
    AIR,
    GRASS,
    DIRT,
    STONE
};

inline const char *to_string(BlockType e) {
    switch (e) {
        case AIR: return "AIR";
        case GRASS: return "GRASS";
        case DIRT: return "DIRT";
        case STONE: return "STONE";
        default: return "unknown";
    }
}
#endif //BLOCKTYPE_H
