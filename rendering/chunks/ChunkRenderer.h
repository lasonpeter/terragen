//
// Created by xenu on 08/05/2025.
//

#ifndef TERRAGEN_CHUNKRENDERER_H
#define TERRAGEN_CHUNKRENDERER_H

#include <cstdint>
#include <unordered_map>
#include "../../procedural/ChunkGovernor.h"

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

class ChunkRenderer{
    std::unordered_map<Int2, ChunkModel> chunkModelCacheMap;
    std::vector<ChunkModel> chunkModelCache{};
    std::vector<ChunkMesh*> chunkMeshesCache{};
    Texture2D textureAtlas;
public:
    void addChunksToBeRendered(std::vector<Chunk*> *chunks, int chunkSize);
    void uploadMeshes();
    void renderChunks();

    void loadTextureAtlas();
};
#endif //TERRAGEN_CHUNKRENDERER_H
