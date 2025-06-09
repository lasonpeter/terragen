//
// Created by lasek on 05.04.25.
//

#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>
#include <vector>
#include "Block.h"
#include "../utilities/Mathf.h"
//

class Chunk {
public:
    Int2 position{};
    Block blocks[65536] = {};

    explicit Chunk(Int2 position_t) {
        position = position_t;
    }

    static void
    generateChunkFaceMasks(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks,
                           int chunk_index_x,
                           int chunk_index_y, std::vector<Chunk *> *chunks, int renderDistance, int chunkPosX,
                           int chunkPosZ);
};

#endif //CHUNK_H
//{
//        uint8_t masks[65536];
//        for (int y = 0; y < 256; ++y) {
//            for (int x = 0; x < 16; ++x) {
//                for (int z = 0; z < 16; ++z) {
//                    //ON Z AXIS
//                    if(z<15) {
//                        if (chunk->blocks[y * 256 + x * 16 + z + 1].isTransparent) {
//                            masks[y * 256 + x * 16 + z]+=FaceMask::Front;
//                        }
//                    }
//                    else{
//                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
//                        masks[y * 256 + x * 16 + z]+=FaceMask::Front;
//                    }
//                    if(z>1){
//                        if (chunk->blocks[y * 256 + x * 16 + z - 1].isTransparent) {
//                            masks[y * 256 + x * 16 + z]+=FaceMask::Back;
//                        }
//                    }else{
//                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
//                        masks[y * 256 + x * 16 + z]+=FaceMask::Back;
//                    }
//                    //ON X AXIS
//                    if(x<15) {
//                        if (chunk->blocks[y * 256 + x * 16 + z + 16].isTransparent) {
//                            masks[y * 256 + x * 16 + z]+=FaceMask::Right;
//                        }
//                    }
//                    else{
//                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
//                        masks[y * 256 + x * 16 + z]+=FaceMask::Right;
//                    }
//                    if(x>1){
//                        if (chunk->blocks[y * 256 + x * 16 + z - 16].isTransparent) {
//                            masks[y * 256 + x * 16 + z]+=FaceMask::Left;
//                        }
//                    }else{
//                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
//                        masks[y * 256 + x * 16 + z]+=FaceMask::Left;
//                    }
//                }
//            }
//        }
//        return masks;
//    }