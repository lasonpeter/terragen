//
// Created by lasek on 05.04.25.
//

#ifndef BLOCK_H
#define BLOCK_H
#include <raylib.h>

#include "BlockType.h"


class Block {
public:
    bool isTransparent = true;
    BlockType blockType = BlockType::AIR;
    Block() = default;
};


#endif //BLOCK_H
