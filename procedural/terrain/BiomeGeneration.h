//
// Created by xenu on 03/04/2025.
//

#ifndef BIOME_GENERATION_H
#define BIOME_GENERATION_H
#include <vector>


class BiomeGeneration {
    const float BIOME_JITTER = 0.980f;
    const float FREQUENCY = 0.01980f;
    private:
    int seed = 0;
    float frequency = FREQUENCY;
public:
    explicit BiomeGeneration(int seed_);
    void generateNoise(float* buffer, int size, int x, int y);
};



#endif //BIOME_GENERATION_H
