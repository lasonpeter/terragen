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


#include "terrain/BiomeType.h"
#include "terrain/NoiseGeneration.h"


void ChunkGovernor::GenerateChunks(int seed, const char *myEncodedTree2D, const char *myEncodedTree3D) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 8);
    std::vector<int> heightPoints(CHUNK_SIZE*CHUNK_SIZE, 0);
    NoiseGeneration biome_generation(seed);
    biome_generation.setEncodedNodeTree(myEncodedTree2D, myEncodedTree3D);
    float heightMountainMin = std::numeric_limits<float>::infinity();
    float heightMountainInvRange{};
    float heightForestMin = std::numeric_limits<float>::infinity();
    float heightForestInvRange{};
    float heightDesertMin = std::numeric_limits<float>::infinity();
    float heightDesertInvRange{};
    float tempMin = std::numeric_limits<float>::infinity();
    float heightTempInvRange{};
    float humidMin = std::numeric_limits<float>::infinity();
    float heightHumidInvRange{};
    /*SetGlobalMinMax(humidMin, heightHumidInvRange, seed, 0.002f, "DQADAAAAzcwMQAoAAAAAAAAAAAAAAACAPwCamRk/AAAAAAA=");*/
    SetGlobalMinMax(humidMin, heightHumidInvRange, seed, 0.002f, "EwAfhes/BwA=");
    SetGlobalMinMax(tempMin, heightTempInvRange, seed, 0.0015f, "DQAEAAAAAAAAQAcAAAAAAD8AAAAAAA==");
    /*SetGlobalMinMax(tempMin, heightTempInvRange, seed, 0.0015f, "EwBxPQo/BwA=");*/
    SetGlobalMinMax(heightMountainMin, heightMountainInvRange, seed, 0.005f, myEncodedTree2D);
    SetGlobalMinMax(heightForestMin, heightForestInvRange, seed, 0.01f, "GQANAAIAAAAAAABAEwDNzMw+CAAAAAAAPwAAAAAAARkABAAAAAAAAABAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAETAOxROD4HAA==");
    SetGlobalMinMax(heightDesertMin, heightDesertInvRange, seed, 0.01f, "GQANAAIAAAAAAABAEwCuR+E+BwAAAAAAPwAAAAAAARkABAAAAAAAAABAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAETAOxROD4HAA==");

    for (int chunk_x = 0; chunk_x < 32; ++chunk_x) {
        for (int chunk_y = 0; chunk_y < 32; ++chunk_y) {
            Chunk* chunk = new Chunk({chunk_x, chunk_y});
            float* heightMapMountain = new float[CHUNK_SIZE * CHUNK_SIZE];
            float* treeMap = new float[CHUNK_SIZE * CHUNK_SIZE];
            float* heightMapForest = new float[CHUNK_SIZE * CHUNK_SIZE];
            float* heightMapDesert = new float[CHUNK_SIZE * CHUNK_SIZE];
            float* caveMap = new float[CHUNK_SIZE * CHUNK_SIZE* CHUNK_HEIGHT];
            float* tempMap = new float[CHUNK_SIZE * CHUNK_SIZE];
            float* humidMap = new float[CHUNK_SIZE * CHUNK_SIZE];
            biome_generation.generateNoise2D(heightMapMountain, CHUNK_SIZE, chunk_x, chunk_y);
            biome_generation.generateNoise2D(heightMapForest, CHUNK_SIZE, chunk_x, chunk_y, 0.01f, "GQANAAIAAAAAAABAEwDNzMw+CAAAAAAAPwAAAAAAARkABAAAAAAAAABAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAETAOxROD4HAA==");
            biome_generation.generateNoise2D(heightMapDesert, CHUNK_SIZE, chunk_x, chunk_y, 0.01f, "GQANAAIAAAAAAABAEwCuR+E+BwAAAAAAPwAAAAAAARkABAAAAAAAAABAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAETAOxROD4HAA==");
            /*biome_generation.generateNoise2D(humidMap, CHUNK_SIZE, chunk_x, chunk_y, 0.002f, "DQADAAAAzcwMQAoAAAAAAAAAAAAAAACAPwCamRk/AAAAAAA=");*/
            biome_generation.generateNoise2D(humidMap, CHUNK_SIZE, chunk_x, chunk_y, 0.002f, "EwAfhes/BwA=");
            biome_generation.generateNoise2D(tempMap, CHUNK_SIZE, chunk_x, chunk_y, 0.0015f, "DQAEAAAAAAAAQAcAAAAAAD8AAAAAAA==");
            /*biome_generation.generateNoise2D(tempMap, CHUNK_SIZE, chunk_x, chunk_y, 0.0015f, "EwBxPQo/BwA=");*/
            biome_generation.generateNoise2D(treeMap, CHUNK_SIZE, chunk_x, chunk_y, 0.05f, "HgANAAMAAAAAAABAHgALAAEAAAAAAAAAAQAAAAAAAAABBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAETAFK4nj8IAAAAAAA/AAAAAAABEwBxPQpACAA=");
            biome_generation.generateNoise3D(caveMap, CHUNK_SIZE,  CHUNK_HEIGHT, chunk_x, chunk_y);

            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {

                    float temp  = GetNormalizeValue(tempMap [z * CHUNK_SIZE + x], tempMin, heightTempInvRange);
                    float humid = GetNormalizeValue(humidMap[z * CHUNK_SIZE + x], humidMin, heightHumidInvRange);

                    float hM = GetNormalizeValue(heightMapMountain[z * CHUNK_SIZE + x], heightMountainMin, heightMountainInvRange);
                    float hF = GetNormalizeValue(heightMapForest  [z * CHUNK_SIZE + x], heightForestMin, heightForestInvRange);
                    float hD = GetNormalizeValue(heightMapDesert  [z * CHUNK_SIZE + x], heightDesertMin, heightDesertInvRange);

                    float wM, wF, wD;
                    BiomeAdvantage(temp, humid, wM, wF, wD);
                    world::Biome biome = pickBiome(wM, wF, wD);

                    float finalH = wM * hM + wF * hF + wD * hD;

                    int h = static_cast<int>( finalH * (CHUNK_HEIGHT - 1) );
                    h = std::clamp(h, 0, CHUNK_HEIGHT - 1) - 100;
                    heightPoints[z * CHUNK_SIZE + x] = h;

                    switch (biome) {
                    case world::Biome::Mountains:
                        for (int y = 0; y < CHUNK_HEIGHT; ++y)
                        {
                            if (y==0) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::BEDROCK);
                            else if ((y <= h)&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]<0.0f))
                            {
                                if (y>200&&y<=230) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::STONE);
                                else if (y>230) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::SNOW);
                                else if (y<=h-5) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::STONE);
                                else if (y<=h-1) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::DIRT);
                                else chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::GRASS);
                            }
                            else
                            {
                                chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::AIR);
                                if (y==h&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]>=0.0f)) heightPoints[z * CHUNK_SIZE + x] = 0;
                            }
                        }
                        for (int tx = 0; tx < CHUNK_SIZE; ++tx)
                        {
                            for (int tz = 0; tz < CHUNK_SIZE; ++tz)
                            {
                                auto v = treeMap[tz * CHUNK_SIZE + tx];
                                /*std::cout<<v<<std::endl;*/
                                v=v*dis(gen);
                                if (v >= 0.01f||tx < 2 || tx > 13 || tz < 2 || tz > 13) continue;

                                int y0 = heightPoints[tx + tz * CHUNK_SIZE];

                                if (y0 < 0 || y0 > 190)
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
                        break;
                    case world::Biome::Forest:
                        for (int y = 0; y < CHUNK_HEIGHT; ++y)
                        {
                            if (y==0) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::BEDROCK);
                            else if ((y <= h)&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]<0.0f))
                                if (y<=h-5) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::STONE);
                                else if (y<=h-1) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::DIRT);
                                else chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::GRASS);
                            else{
                                chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::AIR);
                                if (y==h&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]>=0.0f)) heightPoints[z * CHUNK_SIZE + x] = 0;
                            }
                        }
                        for (int tx = 0; tx < CHUNK_SIZE; ++tx)
                        {
                            for (int tz = 0; tz < CHUNK_SIZE; ++tz)
                            {
                                auto v = treeMap[tz * CHUNK_SIZE + tx];
                                /*std::cout<<v<<std::endl;*/
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
                        break;
                    case world::Biome::Desert:
                        for (int y = 0; y < CHUNK_HEIGHT; ++y)
                        {
                            if (y==0) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::BEDROCK);
                            else if ((y <= h)&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]<0.0f))
                                if (y<=h-5) chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::STONE);
                                else chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::SAND);
                            else{
                                chunk->blocks[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x] = Block(BlockType::AIR);
                                if (y==h&&(caveMap[(y * CHUNK_SIZE + z) * CHUNK_SIZE + x]>=0.0f)) heightPoints[z * CHUNK_SIZE + x] = 0;
                            }
                        }
                        break;
                    }

                }
            }

            /*for (int tx = 0; tx < CHUNK_SIZE; ++tx)
            {
                for (int tz = 0; tz < CHUNK_SIZE; ++tz)
                {
                    auto v = treeMap[tz * CHUNK_SIZE + tx];
                    /*std::cout<<v<<std::endl;#1#
                    v=v*dis(gen);
                    if (v >= 0.04f||tx < 2 || tx > 13 || tz < 2 || tz > 13) continue;

                    int y0 = heightPoints[tx + tz * CHUNK_SIZE];

                    if (y0 < 0 || y0 > 100)
                        continue;

                    /*generowanie pnia#1#
                    for (int dy = 1; dy <= 4; ++dy) {
                        int yy = y0 + dy;
                        if (yy < 0 || yy >= CHUNK_HEIGHT)
                            continue;
                        int idx = (yy * CHUNK_SIZE + tz) * CHUNK_SIZE + tx;
                        chunk->blocks[idx] = Block(BlockType::WOOD);
                    }

                    /*generowanie lisci#1#
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
            }*/


            chunks_.push_back(chunk);
            delete[] treeMap;
            delete[] heightMapMountain;
            delete[] heightMapDesert;
            delete[] heightMapForest;
            delete[] caveMap;
            delete[] tempMap;
            delete[] humidMap;
        }
    }
}


void ChunkGovernor::SetGlobalMinMax(float& Min, float& invRange, int seed, float frequency, const char* code)
{
    NoiseGeneration biome_generation(seed);
    float Max = -std::numeric_limits<float>::infinity();
    for (int chunk_x = 0; chunk_x < 32; ++chunk_x) {
        for (int chunk_y = 0; chunk_y < 32; ++chunk_y) {
            float tempHeightMap[CHUNK_SIZE * CHUNK_SIZE];
            biome_generation.generateNoise2D(tempHeightMap, CHUNK_SIZE, chunk_x, chunk_y, frequency, code);

            for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; ++i) {
                Min = std::min(Min, tempHeightMap[i]);
                Max = std::max(Max, tempHeightMap[i]);
            }
        }
    }
    Min = Min - (Max-Min) * 0.1;
    Max = Max + (Max-Min) * 0.1;
    invRange = (Max != Min) ? (1.0f / (Max - Min)) : 0.0f;
}

float ChunkGovernor::GetNormalizeValue(float& value, float& Min, float& invRange)
{
    float norm = (value - Min) * invRange;
    norm = std::clamp(norm, 0.0f, 1.0f);
    /*int h = static_cast<int>(normalized * (CHUNK_HEIGHT - 1));*/
    /*h = std::clamp(h, 0, CHUNK_HEIGHT - 1) - 100;*/
    return norm;
}

float ChunkGovernor::GetNormalizeValue(float& value)
{
    float norm = value * 0.5f + 0.5f;
    norm = std::clamp(norm, 0.0f, 1.0f);
    return norm;
}

void ChunkGovernor::BiomeAdvantage(float temp, float humid, float& wMountain, float& wForest, float& wDesert)
{
    BiomeGeneration biomValues;
    float Mountain = sqrt(pow(temp-biomValues.mountains.x,2)+pow( humid-biomValues.mountains.y,2))+ 1e-5f;
    float Forest = sqrt(pow(temp-biomValues.forest.x,2)+pow(humid-biomValues.forest.y,2))+ 1e-5f;
    float Desert = sqrt(pow(temp-biomValues.desert.x,2)+pow(humid-biomValues.desert.y,2))+ 1e-5f;
    float iM = 1/Mountain;
    float iF = 1/Forest;
    float iD = 1/Desert;
    float sum = iM + iF + iD;
    wMountain = iM/sum;
    wForest = iF/sum;
    wDesert = iD/sum;
}

world::Biome ChunkGovernor::pickBiome(float wM, float wF, float wD)
{
    if (wM > wF && wM > wD) return world::Biome::Mountains;
    if (wF > wM && wF > wD) return world::Biome::Forest;
    return world::Biome::Desert;
}




