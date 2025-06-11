//
// Created by xenu on 08/05/2025.
//

#ifndef TERRAGEN_CHUNKRENDERER_H
#define TERRAGEN_CHUNKRENDERER_H

#include <cstdint>
#include "../../procedural/ChunkGovernor.h"

struct ChunkMesh{
    Int2 chunkPosition;
    uint8_t chunkFaceMasks[ChunkGovernor::CHUNK_HEIGHT*ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE];
    Mesh mesh = {0};
};

struct SubChunkModel{
    Model model{};
    Vector3 position{};
};

class ChunkRenderer{
    std::vector<SubChunkModel> modelCache{};
    std::vector<ChunkMesh*> chunkMeshesCache{};
    Texture2D textureAtlas;
public:
    void addChunksToBeRendered(std::vector<Chunk*> *chunks, int chunkSize);
    void uploadMeshes();
    void renderChunks();
};
#endif //TERRAGEN_CHUNKRENDERER_H
