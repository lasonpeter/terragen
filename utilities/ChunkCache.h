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

struct ChunkModel{
    Int2 chunkPosition{};
    Model subChunkModels[16]{};
};

class ChunkCache {
private:
    ChunkRenderer* chunkRenderer{};
    std::string Int2ToString(Int2 int2);
public:
    ChunkGovernor chunkGovernor{};
    std::unordered_map<std::string, ChunkModel> chunkModelCache{};
    std::unordered_map<std::string, ChunkMesh*> chunkMeshesCache{};
    explicit ChunkCache(ChunkRenderer* chunkRenderer_t) : chunkRenderer(chunkRenderer_t) {}
    void addChunk(Chunk* chunk);
    void removeChunk(Int2 chunkPosition);
    ChunkModel getChunkModel(Int2 chunkPosition);
    ChunkMesh* getChunkMesh(Int2 chunkPosition);
};


#endif //TERRAGEN_CHUNKCACHE_H
