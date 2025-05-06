//
// Created by xenu on 03/04/2025.
//

#include "BiomeGeneration.h"

#include <FastNoise/FastNoise_Config.h>
#include <FastNoise/Generators/Cellular.h>
#include <FastNoise/Generators/Fractal.h>
#include <FastNoise/Generators/Simplex.h>
#include <FastNoise/FastNoise.h>


BiomeGeneration::BiomeGeneration(int seed_)
{
    seed = seed_;
}

void BiomeGeneration::generateNoise(float* buffer,int size,int x,int y)
{
    auto cellular = FastNoise::NewFromEncodedNodeTree("EQAEAAAA9igcQBAAAAAAQBkAEwDD9Sg/DQAEAAAAAAAgQAkAAGZmJj8AAAAAPwEEAAAAAAAAAEBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM3MTD4AMzMzPwAAAAA/");
    cellular->GenUniformGrid2D(buffer,x,y,size,size,frequency,seed);
}