//
// Created by PC on 18.05.2025.
//

#ifndef TERRAINIMAGE_H
#define TERRAINIMAGE_H

#include <raylib.h>
#include "BiomeGeneration.h"
#include <vector>

class TerrainImage{
public:
    static constexpr int ATLAS_SIZE=256;
    int half = ATLAS_SIZE/2;
    std::vector<float> noiseOutput;
    BiomeGeneration biome_generation = BiomeGeneration(0);

    TerrainImage(int seed, const char *myEncodedTree);

    Color* getNoisePixels();

};

#endif //TERRAINIMAGE_H
