//
// Created by xenu on 08/05/2025.
//

#include <algorithm>
#include "ChunkGovernor.h"

#include <iostream>
#include <limits>
#include <ostream>
#include <random>
#include <vector>

#include "terrain/BiomeGeneration.h"

void ChunkGovernor::GenerateChunks(int seed, const char *myEncodedTree2D, const char *myEncodedTree3D) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 8);
    std::vector<int> heightPoints(CHUNK_SIZE*CHUNK_SIZE, 0);
    BiomeGeneration biome_generation(seed);
    biome_generation.setEncodedNodeTree(myEncodedTree2D, myEncodedTree3D);
    float globalMin = std::numeric_limits<float>::infinity();
    float globalMax = -std::numeric_limits<float>::infinity();

    for (int chunk_x = 0; chunk_x < 32; ++chunk_x) {
        for (int chunk_y = 0; chunk_y < 32; ++chunk_y) {
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
            float* treeMap = new float[CHUNK_SIZE * CHUNK_SIZE];
            float* caveMap = new float[CHUNK_SIZE * CHUNK_SIZE* CHUNK_HEIGHT];
            biome_generation.generateNoise2D(heightMap, CHUNK_SIZE, chunk_x, chunk_y);
            biome_generation.generateNoise2D(treeMap, CHUNK_SIZE, chunk_x, chunk_y, 0.05f, "HgANAAMAAAAAAABAHgALAAEAAAAAAAAAAQAAAAAAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAETAFK4nj8IAAAAAAA/AAAAAAABEwBxPQpACAA=");
            biome_generation.generateNoise3D(caveMap, CHUNK_SIZE,  CHUNK_HEIGHT, chunk_x, chunk_y);

            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {
                    constexpr int max_height = 256;

                    float v = heightMap[z * CHUNK_SIZE + x];
                    float normalized = (v - globalMin) * invRange;

                    int h = static_cast<int>(normalized * (max_height - 1));
                    h = std::clamp(h, 0, max_height - 1) - 100;
                    heightPoints[z * CHUNK_SIZE + x] = h;

                    for (int y = 0; y < max_height; ++y)
                    {
                        if (((y <= h)&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]<0.0f))||y==0)
                            if (y<=h-5) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::STONE);
                            else if (y<=h-1) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::DIRT);
                            else chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::GRASS);
                        else{
                            chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::AIR);
                            if (y==h&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]<0.0f)) heightPoints[z * CHUNK_SIZE + x] = 0;
                        }
                    }
                }
            }

            for (int tx = 0; tx < CHUNK_SIZE; ++tx)
            {
                for (int tz = 0; tz < CHUNK_SIZE; ++tz)
                {
                    auto v = treeMap[tz * CHUNK_SIZE + tx];
                    v=v*dis(gen);
                    if (v >= 0.04f||tx < 2 || tx > 13 || tz < 2 || tz > 13) continue;

                    int y0 = heightPoints[tx + tz * CHUNK_SIZE];

                    if (y0 < 0 || y0 > 100)
                        continue;

                    /*generowanie pnia*/
                    for (int dy = 1; dy <= 4; ++dy) {
                        int yy = y0 + dy;
                        if (yy < 0 || yy >= CHUNK_HEIGHT)
                            continue;
                        int idx = (yy * CHUNK_SIZE + tz) * CHUNK_SIZE + tx;
                        chunk->blocks[idx] = Block(BlockType::WOOD);
                    }

                    /*generowanie lisci*/
                    for (int dx = -2; dx <= 2; ++dx) {
                        for (int dy = 3; dy <= 6; ++dy) {
                            for (int dz = -2; dz <= 2; ++dz) {

                                if (dx*dx + (dy-4)*(dy-4) + dz*dz > 8)
                                    continue;

                                int xx = tx + dx;
                                int yy = y0 + dy;
                                int zz = tz + dz;

                                if (xx < 0 || xx >= CHUNK_SIZE ||
                                    yy < 0 || yy >= CHUNK_HEIGHT ||
                                    zz < 0 || zz >= CHUNK_SIZE)
                                    continue;

                                int idx = (yy * CHUNK_SIZE + zz) * CHUNK_SIZE + xx;

                                if (chunk->blocks[idx].blockType == BlockType::AIR) {
                                    chunk->blocks[idx] = Block(BlockType::STONE);
                                }
                            }
                        }
                    }
                }
            }


            chunks_.push_back(chunk);
            delete[] treeMap;
            delete[] heightMap;
            delete[] caveMap;
        }
    }
}
