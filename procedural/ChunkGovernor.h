//
// Created by xenu on 08/05/2025.
//

#ifndef TERRAGEN_CHUNKGOVERNOR_H
#define TERRAGEN_CHUNKGOVERNOR_H

#include <vector>
#include "Chunk.h"
#include "terrain/generators/BiomeGeneration.h"
class NoiseGeneration;

class ChunkGovernor{
private:
    const float treesDensity = 0.04f;
    Int2 currentCameraPosition_{};
    static void SetGlobalMinMax (float& Min, float& invRange, int seed, float frequency, const char* code);
    static float GetNormalizeValue (float& value, float& Min, float& Max);
    static float GetNormalizeValue (float& value);
    void BiomeAdvantage(float temp, float humid, float& wMountain, float& wForest, float& wDesert);
    world::Biome pickBiome(float wM, float wF, float wD);
public:
    std::vector<Chunk*> chunks_{};
    ChunkGovernor(){
        chunks_ ={};
    }
    void GenerateChunks(int seed, const char *myEncodedTree2D, const char *myEncodedTree3D);

    static const int CHUNK_SIZE=16;
    static const int CHUNK_HEIGHT=256;
    static const int TREE_MAP_SIZE=20;
};

#endif //TERRAGEN_CHUNKGOVERNOR_H
