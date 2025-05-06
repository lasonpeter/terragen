//
// Created by xenu on 06/05/2025.
//

#include "Chunk.h"
#include "../utilities/FaceMask.h"
uint8_t *Chunk::generateChunkFaceMasks(Chunk *chunk,int* face_count) {
        auto* masks = new uint8_t[256 * 16 * 16]{};
        for (int y = 0; y < 256; ++y) {
            for (int x = 0; x < 16; ++x) {
                for (int z = 0; z < 16; ++z) {
                    if(is_transparent((chunk->blocks[y * 256 + x * 16 + z]).blockType)){
                        continue;
                    }
                    //ON Z AXIS
                    if(z<15) {
                        if (is_transparent((chunk->blocks[y * 256 + x * 16 + z + 1]).blockType)) {
                            masks[y * 256 + x * 16 + z]+=FaceMask::Front;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * 256 + x * 16 + z]+=FaceMask::Front;
                        (*face_count)++;
                    }
                    if(z>1){
                        if (is_transparent(chunk->blocks[y * 256 + x * 16 + z - 1].blockType)) {
                            masks[y * 256 + x * 16 + z]+=FaceMask::Back;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * 256 + x * 16 + z]+=FaceMask::Back;
                        (*face_count)++;
                    }
                    //ON X AXIS
                    if(x<15) {
                        if (is_transparent(chunk->blocks[y * 256 + x * 16 + z + 16].blockType)) {
                            masks[y * 256 + x * 16 + z]+=FaceMask::Right;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * 256 + x * 16 + z]+=FaceMask::Right;
                        (*face_count)++;
                    }
                    if(x>1){
                        if (is_transparent(chunk->blocks[y * 256 + x * 16 + z - 16].blockType)) {
                            masks[y * 256 + x * 16 + z]+=FaceMask::Left;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * 256 + x * 16 + z]+=FaceMask::Left;
                        (*face_count)++;
                    }
                    //ON Y AXIS
                    if(y<255) {
                        if (is_transparent(chunk->blocks[y * 256 + x * 16 + z + 256].blockType)) {
                            masks[y * 256 + x * 16 + z]+=FaceMask::Top;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * 256 + x * 16 + z]+=FaceMask::Top;
                        (*face_count)++;
                    }
                    if(y>1){
                        if (is_transparent(chunk->blocks[y * 256 + x * 16 + z - 256].blockType)) {
                            masks[y * 256 + x * 16 + z]+=FaceMask::Bottom;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * 256 + x * 16 + z]+=FaceMask::Bottom;
                        (*face_count)++;
                    }
                }
            }
        }
        return masks;
    }