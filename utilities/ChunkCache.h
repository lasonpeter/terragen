//
// Created by lasek on 11.06.25.
//

#ifndef CHUNKCACHE_H
#define CHUNKCACHE_H
#include <vector>
#include <unordered_map>
#include <string>
#include <raylib.h>
#include "../utilities/Mathf.h"
#include "../procedural/Chunk.h"

// Forward declarations
class Chunk;
struct ChunkMesh;
struct ChunkModel;
class ChunkCache {
  public:
    std::unordered_map<std::string,Chunk*> chunk_cache_;
    std::unordered_map<std::string,ChunkMesh*> chunk_mesh_cache_;
    std::unordered_map<std::string,ChunkModel*> chunk_model_cache_;
    void addChunk(Chunk* chunk);
    void removeChunk(Int2 chunkId);
};

#endif //CHUNKCACHE_H
