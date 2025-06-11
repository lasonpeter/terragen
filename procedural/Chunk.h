//
// Created by lasek on 05.04.25.
//

#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>
#include <vector>
#include "Block.h"
#include "../utilities/Mathf.h"
#include "../rendering/chunks/ChunkRenderer.h"

// Forward declaration

class Chunk {
public:
    Int2 position{};
    Block blocks[65536] = {};

    explicit Chunk(Int2 position_t) {
        position = position_t;
    }

    static void generateChunkFaceMasks(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks);
};


struct ChunkModel{
    SubChunkModel chunk_models[16]{};
};
#endif //CHUNK_H