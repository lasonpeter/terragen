//
// Created by xenu on 08/05/2025.
//

#ifndef TERRAGEN_CHUNKRENDERER_H
#define TERRAGEN_CHUNKRENDERER_H

#include <cstdint>
#include <raylib.h>
#include <vector>
#include "../../utilities/Mathf.h"

// Forward declarations
class ChunkCache;
class Chunk;

// Define constants to avoid circular dependency
constexpr int CHUNK_SIZE = 16;

struct SubChunkMesh{
    uint8_t *chunkFaceMasks = new uint8_t[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE]{};
    Mesh* mesh = {0};

    SubChunkMesh() = default;
    
/*    ~SubChunkMesh(){
        UnloadMesh(mesh);
        delete[] chunkFaceMasks;
    }*/
};

struct ChunkMesh {
    Int2 chunkPosition;
    SubChunkMesh* meshes[16]{};
};

struct SubChunkModel{
    Model model{};
    Vector3 position{};
};

class ChunkRenderer{
    std::vector<SubChunkModel> modelCache{};
public:
    Texture2D textureAtlas{};
    static ChunkMesh *renderMesh(Chunk *chunk);

    static void renderChunks(ChunkCache *chunkCache);

    static void uploadMeshes(ChunkCache *chunkCache);

    void uploadTextureAtlas();
};
#endif //TERRAGEN_CHUNKRENDERER_H