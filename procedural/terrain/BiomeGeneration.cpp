//
// Created by xenu on 03/04/2025.
//

#include "BiomeGeneration.h"

#include <stdexcept>
#include <FastNoise/FastNoise_Config.h>
#include <FastNoise/Generators/Cellular.h>
#include <FastNoise/Generators/Fractal.h>
#include <FastNoise/Generators/Simplex.h>
#include <FastNoise/FastNoise.h>



BiomeGeneration::BiomeGeneration(int seed_)
{
    seed = seed_;
}

void BiomeGeneration::generateNoise(float *buffer, int size, int x, int y)
{
    auto fn = FastNoise::NewFromEncodedNodeTree(encodedNodeTree);

    if (fn)
    {
        fn->GenUniformGrid2D(buffer, x, y, size, size, frequency, seed);
    }
    else
    {
        throw std::runtime_error("Failed to load encoded node tree");
    }
}
