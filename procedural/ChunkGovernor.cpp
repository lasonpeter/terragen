//
// Created by xenu on 08/05/2025.
//

#include <algorithm>
#include "ChunkGovernor.h"

#include <iostream>
#include <limits>
#include <ostream>

#include "terrain/BiomeGeneration.h"

void ChunkGovernor::GenerateChunks(int seed, const char *myEncodedTree) {
    BiomeGeneration biome_generation(seed);
    biome_generation.setEncodedNodeTree(myEncodedTree);
    float globalMin = std::numeric_limits<float>::infinity();
    float globalMax = -std::numeric_limits<float>::infinity();

    for (int chunk_x = 0; chunk_x < 256; ++chunk_x) {
        for (int chunk_y = 0; chunk_y < 256; ++chunk_y) {
            float tempHeightMap[CHUNK_SIZE * CHUNK_SIZE];
            biome_generation.generateNoise(tempHeightMap, CHUNK_SIZE, chunk_x, chunk_y);

            for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; ++i) {
                globalMin = std::min(globalMin, tempHeightMap[i]);
                globalMax = std::max(globalMax, tempHeightMap[i]);
            }
        }
    }
    float invRange = (globalMax != globalMin) ? (1.0f / (globalMax - globalMin)) : 0.0f;

    for (int chunk_x = 0; chunk_x < 256; ++chunk_x) {
        for (int chunk_y = 0; chunk_y < 256; ++chunk_y) {
            Chunk* chunk = new Chunk({chunk_x, chunk_y});
            float* heightMap = new float[CHUNK_SIZE * CHUNK_SIZE];
            biome_generation.generateNoise(heightMap, CHUNK_SIZE, chunk_x, chunk_y);

            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {
                    constexpr int max_height = 256;

                    float v = heightMap[z * CHUNK_SIZE + x];
                    float normalized = (v - globalMin) * invRange;

                    int h = static_cast<int>(normalized * (max_height - 1));
                    h = std::clamp(h, 0, max_height - 1) - 120;

                    for (int y = 0; y < max_height; ++y) {
                        if (y <= h)
                            chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::DIRT);
                        else
                            chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::AIR);
                    }
                }
            }

            chunks_.push_back(chunk);
            delete[] heightMap;
        }
    }
    /*for (int chunk_position_x = 0; chunk_position_x < 16; ++chunk_position_x) {
        for (int chunk_position_y = 0; chunk_position_y < 16; ++chunk_position_y) {
            auto *chunk = new Chunk({chunk_position_x,chunk_position_y});
            auto* heightMap= new float[CHUNK_SIZE*CHUNK_SIZE];
            biome_generation.generateNoise(heightMap,CHUNK_SIZE,chunk_position_x,chunk_position_y);

            float minG =  std::numeric_limits<float>::infinity();
            float maxG = -std::numeric_limits<float>::infinity();
            for (int i=0;i<CHUNK_SIZE*CHUNK_SIZE;i++) {
                minG = std::min(minG, heightMap[i]);
                maxG = std::max(maxG, heightMap[i]);
            }
            std::cout<<minG<<" "<<maxG<<std::endl;
            float invRangeG = 1.0f / (maxG - minG);

            for (int x = 0; x < CHUNK_SIZE; x++) {
                for (int z = 0; z < CHUNK_SIZE; z++) {
                    constexpr int max_height = 256;

                    float v = heightMap[z * CHUNK_SIZE + x];

                    v = (v - minG) * invRangeG;
                    /*std::cout<<v<<std::endl;#1#
                    /*v = std::clamp(v, -1.0f, 1.0f);#1#
                    /*float norm = (v + 1.0f)*0.52f;#1#
                    int h = static_cast<int>(v * (max_height - 1));
                    h = std::clamp(h, 0, max_height -1) -180;

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
    }*/
}
