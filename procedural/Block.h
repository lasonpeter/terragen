//
// Created by lasek on 05.04.25.
//

#ifndef BLOCK_H
#define BLOCK_H
#include <raylib.h>

#include "BlockType.h"


class Block {
public:
    Vector3 position{};
    bool isTransparent = true;
    BlockType blockType = AIR;
    Block() {
        position = Vector3(0, 0, 0);
    }
    explicit Block(Vector3 position_t) {
        this->position = position_t;
    }
};


#endif //BLOCK_H
