//
// Created by xenu on 08/05/2025.
//

#ifndef TERRAGEN_CHUNKGOVERNOR_H
#define TERRAGEN_CHUNKGOVERNOR_H

#include <vector>
#include "Chunk.h"

class ChunkGovernor{
private:

    Int2 currentCameraPosition_{};
public:
    std::vector<Chunk*> chunks_{};
    ChunkGovernor(){
        chunks_ ={};
    }
    void GenerateChunks(int seed, const char *myEncodedTree2D, const char *myEncodedTree3D);

    static const int CHUNK_SIZE=16;
    static const int CHUNK_HEIGHT=256;
    static const int TREE_MAP_SIZE=20;
    static constexpr int SUB_CHUNK_SIZE=CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE;
    static constexpr int CHUNK_SLICE_SIZE=CHUNK_SIZE*CHUNK_SIZE;
};

#endif //TERRAGEN_CHUNKGOVERNOR_H
