//
// Created by lasek on 05.04.25.
//

#ifndef BLOCK_H
#define BLOCK_H
#include <raylib.h>

#include "BlockType.h"


class Block {
public:
    BlockType blockType = BlockType::AIR;
    Block() = default;

    explicit Block(BlockType block_type);
};


#endif //BLOCK_H
