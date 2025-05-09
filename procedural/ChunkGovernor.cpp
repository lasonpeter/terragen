//
// Created by xenu on 08/05/2025.
//

#include <algorithm>
#include "ChunkGovernor.h"
#include "terrain/BiomeGeneration.h"

void ChunkGovernor::GenerateChunks() {
    BiomeGeneration biome_generation(1337);
    const char *myEncodedTree = "GQATAClcjz4IAAETAMP1KD8NAAQAAAAAACBACQAAZmYmPwAAAAA/";
    biome_generation.setEncodedNodeTree(myEncodedTree);
    for (int chunk_position_x = 0; chunk_position_x < 5; ++chunk_position_x) {
        for (int chunk_position_y = 0; chunk_position_y < 5; ++chunk_position_y) {
            auto *chunk = new Chunk({chunk_position_x,chunk_position_y});
            auto* heightMap= new float[CHUNK_SIZE*CHUNK_SIZE];
            biome_generation.generateNoise(heightMap,CHUNK_SIZE,chunk_position_x,chunk_position_y);
            for (int x = 0; x < CHUNK_SIZE; x++) {
                for (int z = 0; z < CHUNK_SIZE; z++) {
                    constexpr int max_height = 256;

                    float v = heightMap[z * CHUNK_SIZE + x];
                    v = std::clamp(v, -1.0f, 1.0f);
                    float norm = (v + 1.0f)*0.52f;
                    int h = static_cast<int>(norm * (max_height - 1));
                    h = std::clamp(h, 0, max_height -1) -120;

                    for (int y = 0; y < max_height; ++y) {
                        if (y <= h)
                            chunk->blocks[(y*CHUNK_SIZE + z)*CHUNK_SIZE + x] = Block(BlockType::DIRT);
                        else chunk->blocks[(y*CHUNK_SIZE + z)*CHUNK_SIZE + x] = Block(BlockType::AIR);
                    }
                }
            }
            chunks_.push_back(chunk);
            delete[] heightMap;
        }
    }
}
