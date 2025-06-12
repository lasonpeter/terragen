//
// Created by xenu on 08/05/2025.
//
#include "raylib.h"
#include <iostream>
#include <bitset>

#include "raymath.h"
#include "raygui.h"
#include "ChunkRenderer.h"
#include "../StaticRenderer.h"

void ChunkRenderer::renderChunks() {
    for (auto& chunkMeshPair: chunkCache->chunkMeshesCache) {
        ChunkMesh* chunkMesh = chunkMeshPair.second;
        for (int i = 0; i < 16; ++i) {
            // Calculate position for this subchunk
            float posX = static_cast<float>(chunkMesh->chunkPosition.y) * ChunkGovernor::CHUNK_SIZE;
            float posY = static_cast<float>(i * ChunkGovernor::CHUNK_SIZE);
            float posZ = static_cast<float>(chunkMesh->chunkPosition.x) * ChunkGovernor::CHUNK_SIZE;
            
            // Create transformation matrix for position and draw mesh
            DrawMesh(chunkMesh->meshes[i].mesh, material, MatrixTranslate(posX, posY, posZ));
        }
    }
}

void ChunkRenderer::loadTextureAtlas() {
    Image atlasImage = LoadImage("data/textures/blocks/blocks.png");
    textureAtlas = LoadTextureFromImage(atlasImage);
    textureAtlas.format = PixelFormat::PIXELFORMAT_UNCOMPRESSED_R16G16B16;
    UnloadImage(atlasImage);
    
    // Initialize the material for DrawMesh
    material = LoadMaterialDefault();
    material.maps[MATERIAL_MAP_DIFFUSE].texture = textureAtlas;
}