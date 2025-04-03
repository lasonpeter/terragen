//
// Created by xenu on 03/04/2025.
//

#include "height_map_gen.h"

#include <FastNoise/FastNoise.h>

const float BIOME_JITTER = 0.980f;
std::vector<float> height_map_gen::height_map_gen(const int size_)
{
    auto biomeNoise =FastNoise::New<FastNoise::CellularDistance>();
    biomeNoise->SetJitterModifier(BIOME_JITTER);
    biomeNoise->SetDistanceFunction(FastNoise::DistanceFunction::Hybrid);
}