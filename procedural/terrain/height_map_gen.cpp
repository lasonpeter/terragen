//
// Created by xenu on 03/04/2025.
//

#include "height_map_gen.h"

#include <FastNoise/FastNoise.h>

const float BIOME_JITTER = 0.980f;
height_map_gen::height_map_gen()
{
    FastNoise::SmartNode<FastNoise::Cellular> biomeNoise = FastNoise::New<FastNoise::Cellular>();
    biomeNoise->SetJitterModifier(BIOME_JITTER);
    biomeNoise->SetDistanceFunction(FastNoise::DistanceFunction::Hybrid);
}
