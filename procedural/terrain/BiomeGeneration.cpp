//
// Created by xenu on 03/04/2025.
//

#include "BiomeGeneration.h"

#include <FastNoise/FastNoise_Config.h>
#include <FastNoise/Generators/Cellular.h>


BiomeGeneration::BiomeGeneration(int seed_)
{
    seed = seed_;
}

void BiomeGeneration::generate(float* buffer,int size,int x,int y)
{
    auto biomeNoise =FastNoise::New<FastNoise::CellularValue>();
    biomeNoise->SetJitterModifier(BIOME_JITTER);
    biomeNoise->SetDistanceFunction(FastNoise::DistanceFunction::Hybrid);
    biomeNoise->GenUniformGrid2D(buffer,x,y,size,size,frequency,seed);
}
