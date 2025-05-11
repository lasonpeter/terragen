//
// Created by xenu on 11/05/2025.
//

#ifndef TERRAGEN_QUANTUMCHUNK_H
#define TERRAGEN_QUANTUMCHUNK_H

#include <cstdint>
#include "../../procedural/ChunkGovernor.h"

struct QuantumChunk{
    uint8_t chunkFaceMasks[ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE]{};
    Mesh mesh = {0};
};
#endif //TERRAGEN_QUANTUMCHUNK_H
