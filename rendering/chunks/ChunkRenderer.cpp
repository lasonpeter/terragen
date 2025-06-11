//
// Created by xenu on 08/05/2025.
//

#include <iostream>
#include "ChunkRenderer.h"
#include "../StaticRenderer.h"



void ChunkRenderer::renderChunks() {
    {
        {
            for (auto chunkModels: chunkCache->chunkModelCache) {
                    for (int i = 0; i < 16; ++i) {
                        DrawModel(chunkModels.second.subChunkModels[i],Vector3{static_cast<float>(chunkModels.second.chunkPosition.y) * ChunkGovernor::CHUNK_SIZE,static_cast<float>(i * ChunkGovernor::CHUNK_SIZE),static_cast<float>(chunkModels.second.chunkPosition.x) *ChunkGovernor::CHUNK_SIZE}, 1.0f, WHITE);
                    }
                }
            }
        }
    }


void ChunkRenderer::loadTextureAtlas() {
    Image atlasImage = LoadImage("data/textures/blocks/blocks.png");
    textureAtlas = LoadTextureFromImage(atlasImage);
    textureAtlas.format = PixelFormat::PIXELFORMAT_UNCOMPRESSED_R16G16B16;
    UnloadImage(atlasImage);
}

