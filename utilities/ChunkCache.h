//
// Created by lasek on 11.06.25.
//

#ifndef CHUNKCACHE_H
#define CHUNKCACHE_H
#include <vector>

#include "../rendering/chunks/ChunkRenderer.h"


class Chunk;

class ChunkCache {
  std::vector<Chunk*> chunk_cache_;
  std::vector<ChunkMesh*> chunk_mesh_cache_;
  public:
  void addChunk(Chunk* chunk);
  void invalidateChunk(Chunk* chunk);
  void removeChunk(long chunkId);
  void
};



#endif //CHUNKCACHE_H
