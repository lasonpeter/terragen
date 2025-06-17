//
// Created by xenu on 03/04/2025.
//

#include "NoiseGeneration.h"

#include <stdexcept>
#include <FastNoise/FastNoise_Config.h>
#include <FastNoise/Generators/Cellular.h>
#include <FastNoise/Generators/Fractal.h>
#include <FastNoise/Generators/Simplex.h>
#include <FastNoise/FastNoise.h>



NoiseGeneration::NoiseGeneration(int seed_)
{
    seed = seed_;
}


void NoiseGeneration::generateNoise2D(float *buffer, int size, int x, int y)
{
    auto fn = FastNoise::NewFromEncodedNodeTree(encodedNodeTree2D);

    if (fn)
    {
        fn->GenUniformGrid2D(buffer, x*size, y*size, size, size, frequency, seed);
    }
    else
    {
        throw std::runtime_error("Failed to load encoded node tree");
    }
}

void NoiseGeneration::generateNoise2D(float* buffer, int size, int x, int y, float frequency, const char* encodedTree)
{
    auto fn = FastNoise::NewFromEncodedNodeTree(encodedTree);
    if (fn)
    {
        fn->GenUniformGrid2D(buffer, x*size, y*size, size, size, frequency, seed);
    }
    else
    {
        throw std::runtime_error("Failed to load encoded node tree");
    }
}

void NoiseGeneration::generateNoise3D(float* buffer, int size, int size_height, int x, int y)
{
    auto fn = FastNoise::NewFromEncodedNodeTree(encodedNodeTree3D);

    if (fn)
    {
        fn->GenUniformGrid3D(buffer, x*size, y*size, 0, size, size, size_height, frequency, seed);
    }
    else
    {
        throw std::runtime_error("Failed to load encoded node tree");
    }
}
