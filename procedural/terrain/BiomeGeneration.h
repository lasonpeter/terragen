//
// Created by xenu on 03/04/2025.
//

#ifndef BIOME_GENERATION_H
#define BIOME_GENERATION_H
#include <vector>


class BiomeGeneration {

    const float BIOME_JITTER = 0.980f;
    const float FREQUENCY = 0.005f;
    int seed = 0;
    float frequency = FREQUENCY;

public:
    void setEncodedNodeTree(const char* tree2D, const char* tree3D) { encodedNodeTree2D = tree2D; encodedNodeTree3D = tree3D; }
    void setSeed(int seed_) { seed = seed_; }
    explicit BiomeGeneration(int seed_);
    ///
    /// \param buffer
    /// \param size size of chunk being rendered ( will be made constant)
    /// \param x position of chunk to render
    /// \param y position of chunk to render
    void generateNoise2D(float* buffer, int size, int x, int y);
    void generateNoise3D(float* buffer, int size, int size_height , int x, int y, int z);
private:
    const char* encodedNodeTree2D = nullptr; // Zakodowane drzewo
    const char* encodedNodeTree3D = nullptr;
};



#endif //BIOME_GENERATION_H

