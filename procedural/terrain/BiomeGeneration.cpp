//
// Created by xenu on 03/04/2025.
//

#include "BiomeGeneration.h"

#include <FastNoise/FastNoise_Config.h>
#include <FastNoise/Generators/Cellular.h>
#include <FastNoise/Generators/Fractal.h>
#include <FastNoise/Generators/Simplex.h>


BiomeGeneration::BiomeGeneration(int seed_)
{
    seed = seed_;
}

void BiomeGeneration::generateNoise(float* buffer,int size,int x,int y)
{
    auto cellural = FastNoise::New<FastNoise::CellularValue>();
    cellural->SetJitterModifier(BIOME_JITTER);
    cellural->SetDistanceFunction(FastNoise::DistanceFunction::Hybrid);
    cellural->GenUniformGrid2D(buffer,x,y,size,size,frequency,seed);
}