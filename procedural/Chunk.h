//
// Created by lasek on 05.04.25.
//

#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>
#include <vector>
#include "Block.h"
#include "../utilities/Mathf.h"
//

class Chunk {
public:
    long chunkId{};
    Int2 position{};
    Block blocks[65536] = {};

    explicit Chunk(Int2 position_t) {
        position = position_t;
    }

    explicit Chunk(Int2 position_t,long chunkId_t) {
        chunkId = chunkId_t;
        position = position_t;
    }

    static void generateChunkFaceMasks(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks,
                           int chunk_index_x,
                           int chunk_index_y, std::vector<Chunk *> *chunks, int renderDistance, int chunkPosX,
                           int chunkPosZ);
};

#endif //CHUNK_H
