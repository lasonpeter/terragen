//
// Created by xenu on 08/05/2025.
//

#ifndef TERRAGEN_CHUNKRENDERER_H
#define TERRAGEN_CHUNKRENDERER_H
#pragma once
#include <cstdint>
#include <unordered_map>
#include "../../procedural/ChunkGovernor.h"
#include "../../utilities/ChunkCache.h"

class ChunkModel;
class ChunkMesh;
class ChunkCache;
class ChunkRenderer{
    std::vector<ChunkMesh*> chunkMeshesCache{};
    ChunkCache* chunkCache;
    Material material;  // Material to use with DrawMesh
public:
    void uploadMeshes();
    void renderChunks();
    void addChunkCache(ChunkCache* pChunkCache) { this->chunkCache = pChunkCache;}

    void loadTextureAtlas();

    Texture2D textureAtlas;
};
#endif //TERRAGEN_CHUNKRENDERER_H
