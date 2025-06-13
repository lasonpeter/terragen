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
    Int2 position{};
    Block blocks[65536] = {};

    explicit Chunk(Int2 position_t) {
        position = position_t;
    }

    static void
    generateChunkFaceMasks(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks);
    
static void
    generateChunkFaceMasksWithNeighbors(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks,
                                        const Chunk *chunkLeft, const Chunk *chunkRight, 
                                        const Chunk *chunkFront, const Chunk *chunkBack);
};

#endif //CHUNK_H
