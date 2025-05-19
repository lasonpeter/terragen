//
// Created by PC on 18.05.2025.
//

#include "TerrainImage.h"
#include <cstdint>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <raylib.h>
#include "raymath.h"


/*
const char *myEncodedTree = "GQATAClcjz4IAAETAMP1KD8NAAQAAAAAACBACQAAZmYmPwAAAAA/";
biome_generation.setEncodedNodeTree(myEncodedTree);
*/




TerrainImage::TerrainImage(int seed, const char *myEncodedTree) : noiseOutput(ATLAS_SIZE*ATLAS_SIZE)
{
    biome_generation.setSeed(seed);
    biome_generation.setEncodedNodeTree(myEncodedTree);
}

Color* TerrainImage::getNoisePixels()
{
    biome_generation.generateNoise(noiseOutput.data(),ATLAS_SIZE,-half,-half);

    auto* noisePixels = new Color[ATLAS_SIZE*ATLAS_SIZE];

    for (int y = 0; y < ATLAS_SIZE; y++)
    {
        for (int x = 0; x < ATLAS_SIZE; x++)
        {
            float val = noiseOutput[y * ATLAS_SIZE + x];
            /*std::cout<<val<<std::endl;*/
            auto v = std::clamp(val, -1.0f, 1.0f);
            float norm = (v + 1.0f)*0.5f;
            int rounded = std::lround( norm * 255.0f );
            if (rounded < 0)   rounded = 0;
            if (rounded > 255) rounded = 255;

            auto c = static_cast<uint8_t>( rounded );
            noisePixels[(ATLAS_SIZE-1-y)*ATLAS_SIZE + x] = Color{ c, c, c, 255 };
        }
    }
    return  noisePixels;
}
