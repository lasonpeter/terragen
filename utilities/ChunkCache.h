//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_CHUNKCACHE_H
#define TERRAGEN_CHUNKCACHE_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <future>
#include "../procedural/ChunkGovernor.h"
#include "ThreadPool.h"

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
    ThreadPool meshThreadPool{std::max(1u, std::thread::hardware_concurrency() / 2)}; // Use half of available threads
    std::unordered_map<std::string, std::future<ChunkMesh*>> pendingMeshes{};
    static std::string Int2ToString(Int2 int2);
public:
    ChunkGovernor chunkGovernor{};
    std::unordered_map<std::string, ChunkMesh*> chunkMeshesCache{};
    std::unordered_map<std::string, Chunk*> chunkCache{};
    explicit ChunkCache(ChunkRenderer* chunkRenderer_t) : chunkRenderer(chunkRenderer_t) {}

    void loadMesh(Chunk *chunk);
    
    // Generate mesh in a worker thread
    ChunkMesh* generateMeshAsync(Chunk* chunk, const Chunk* chunkLeft, const Chunk* chunkRight, 
                               const Chunk* chunkFront, const Chunk* chunkBack);
    
    // Check for completed mesh generations
    void updatePendingMeshes();

    void loadChunk(Chunk *chunk);

    void addChunk(Chunk* chunk);

    void regenerateChunkMesh(Chunk *chunk);

    void removeChunk(Int2 chunkPosition);

    void unloadChunk(Int2 chunkPosition);

    void unloadMesh(Int2 chunkPosition);

    ChunkMesh* getChunkMesh(Int2 chunkPosition);
    Chunk* getChunk(Int2 chunkPosition);
};


#endif //TERRAGEN_CHUNKCACHE_H
