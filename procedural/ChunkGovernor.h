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
    static constexpr int CHUNK_SIZE=16;
    static constexpr int CHUNK_HEIGHT=256;
    static constexpr int SUB_CHUNK_SIZE=CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE;
    static constexpr int CHUNK_SLICE_SIZE=CHUNK_SIZE*CHUNK_SIZE;
};

#endif //TERRAGEN_CHUNKGOVERNOR_H
