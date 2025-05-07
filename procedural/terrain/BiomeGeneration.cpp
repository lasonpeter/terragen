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
    auto cellular = FastNoise::NewFromEncodedNodeTree("GQAbABMAuB5FQAcAARMAj8LlQAcAAI/CdT4=");
    cellular->GenUniformGrid3D(buffer,0,x,y,16,256,16,frequency,seed);
}