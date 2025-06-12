//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_CHUNKCACHE_H
#define TERRAGEN_CHUNKCACHE_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include "../procedural/ChunkGovernor.h"

// Forward declarations
class ChunkRenderer;

struct SubChunkMesh{
    uint8_t *chunkFaceMasks = new uint8_t[ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE]{};
    Mesh mesh = {0};
};

struct ChunkMesh {
    Int2 chunkPosition{};
    SubChunkMesh meshes[16]{};
};

// No longer need ChunkModel struct since we're using DrawMesh directly

class ChunkCache {
private:
    ChunkRenderer* chunkRenderer{};
    std::string Int2ToString(Int2 int2);
public:
    ChunkGovernor chunkGovernor{};
    std::unordered_map<std::string, ChunkMesh*> chunkMeshesCache{};
    std::unordered_map<std::string, Chunk*> chunkCache{};
    explicit ChunkCache(ChunkRenderer* chunkRenderer_t) : chunkRenderer(chunkRenderer_t) {}
    void addChunk(Chunk* chunk);
    void removeChunk(Int2 chunkPosition);
    ChunkMesh* getChunkMesh(Int2 chunkPosition);
    Chunk* getChunk(Int2 chunkPosition);
};


#endif //TERRAGEN_CHUNKCACHE_H
