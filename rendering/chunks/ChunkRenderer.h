//
// Created by xenu on 08/05/2025.
//

#ifndef TERRAGEN_CHUNKRENDERER_H
#define TERRAGEN_CHUNKRENDERER_H

#include <cstdint>
#include "../../procedural/ChunkGovernor.h"

struct SubChunkMesh{
    uint8_t *chunkFaceMasks = new uint8_t[ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE]{};
    Mesh mesh = {0};
};

struct ChunkMesh {
    Int2 chunkPosition;
    SubChunkMesh meshes[16]{};
};

class ChunkRenderer{
    std::vector<ChunkMesh*> chunkMeshesCache{};
    Texture2D textureChecked;
public:
    void addChunksToBeRendered(std::vector<Chunk*> *chunks);
    void uploadMeshes();
    void renderChunks();
};
#endif //TERRAGEN_CHUNKRENDERER_H
