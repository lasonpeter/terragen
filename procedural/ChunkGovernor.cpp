//
// Created by xenu on 08/05/2025.
//

#include <algorithm>
#include "ChunkGovernor.h"

#include <iostream>
#include <limits>
#include <ostream>

#include "terrain/BiomeGeneration.h"

void ChunkGovernor::GenerateChunks(int seed, const char *myEncodedTree2D, const char *myEncodedTree3D) {
    BiomeGeneration biome_generation(seed);
    biome_generation.setEncodedNodeTree(myEncodedTree2D, myEncodedTree3D);
    float globalMin = std::numeric_limits<float>::infinity();
    float globalMax = -std::numeric_limits<float>::infinity();

    for (int chunk_x = 0; chunk_x < 16; ++chunk_x) {
        for (int chunk_y = 0; chunk_y < 16; ++chunk_y) {
            float tempHeightMap[CHUNK_SIZE * CHUNK_SIZE];
            biome_generation.generateNoise2D(tempHeightMap, CHUNK_SIZE, chunk_x, chunk_y);

            for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; ++i) {
                globalMin = std::min(globalMin, tempHeightMap[i]);
                globalMax = std::max(globalMax, tempHeightMap[i]);
            }
        }
    }
    globalMin = globalMin - (globalMax-globalMin) * 0.1;
    globalMax = globalMax + (globalMax-globalMin) * 0.1;

    float invRange = (globalMax != globalMin) ? (1.0f / (globalMax - globalMin)) : 0.0f;

    for (int chunk_x = 0; chunk_x < 16; ++chunk_x) {
        for (int chunk_y = 0; chunk_y < 16; ++chunk_y) {
            Chunk* chunk = new Chunk({chunk_x, chunk_y});
            float* heightMap = new float[CHUNK_SIZE * CHUNK_SIZE];
            float* caveMap = new float[CHUNK_SIZE * CHUNK_SIZE* CHUNK_HEIGHT];
            biome_generation.generateNoise2D(heightMap, CHUNK_SIZE, chunk_x, chunk_y);
            biome_generation.generateNoise3D(caveMap, CHUNK_SIZE,  CHUNK_HEIGHT, chunk_x, chunk_y);

            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {
                    constexpr int max_height = 256;

                    float v = heightMap[z * CHUNK_SIZE + x];
                    float normalized = (v - globalMin) * invRange;

                    int h = static_cast<int>(normalized * (max_height - 1));
                    h = std::clamp(h, 0, max_height - 1);

                    for (int y = 0; y < max_height; ++y) {
                        if (((y <= h)&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]<0.0f)) || y==0) {
                            if (y <= h - 5) {
                                chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::STONE);
                            } else if (y <= h - 1) {
                                chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::DIRT);
                            } else {
                                chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::GRASS);
                            }
                        }
                        else{
                            chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::AIR);
                        }
                    }
                }
            }

            chunks_.push_back(chunk);
            delete[] heightMap;
            delete[] caveMap;
        }
    }
}
