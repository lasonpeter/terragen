//
// Created by xenu on 03/04/2025.
//

#ifndef BIOME_GENERATION_H
#define BIOME_GENERATION_H
#include <vector>


class BiomeGeneration {

    const float BIOME_JITTER = 0.980f;
    const float FREQUENCY = 0.005f;
private:
    int seed = 0;
    float frequency = FREQUENCY;

public:
    void setEncodedNodeTree(const char* tree) { encodedNodeTree = tree; }
    explicit BiomeGeneration(int seed_);
    ///
    /// \param buffer
    /// \param size size of chunk being rendered ( will be made constant)
    /// \param x position of chunk to render
    /// \param y position of chunk to render
    void generateNoise(float* buffer, int size, int x, int y);
private:
    const char* encodedNodeTree = nullptr; // Zakodowane drzewo
};



#endif //BIOME_GENERATION_H

