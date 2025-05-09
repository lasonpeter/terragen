//
// Created by xenu on 06/05/2025.
//

#include "Chunk.h"

#include "ChunkGovernor.h"
#include "../utilities/FaceMask.h"
uint8_t *Chunk::generateChunkFaceMasks(Chunk *chunk,int* face_count) {
        auto* masks = new uint8_t[ChunkGovernor::CHUNK_HEIGHT * ChunkGovernor::CHUNK_SIZE * ChunkGovernor::CHUNK_SIZE]{};
        for (int y = 0; y < ChunkGovernor::CHUNK_HEIGHT; ++y) {
            for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
                for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                    if(is_transparent((chunk->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]).blockType)){
                        continue;
                    }
                    //ON Z AXIS
                    if(z<15) {
                        if (is_transparent((chunk->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z + 1]).blockType)) {
                            masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Front;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Front;
                        (*face_count)++;
                    }
                    if(z>1){
                        if (is_transparent(chunk->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z - 1].blockType)) {
                            masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Back;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Back;
                        (*face_count)++;
                    }
                    //ON X AXIS
                    if(x<15) {
                        if (is_transparent(chunk->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z + ChunkGovernor::CHUNK_SIZE].blockType)) {
                            masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Right;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Right;
                        (*face_count)++;
                    }
                    if(x>1){
                        if (is_transparent(chunk->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z - ChunkGovernor::CHUNK_SIZE].blockType)) {
                            masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Left;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Left;
                        (*face_count)++;
                    }
                    //ON Y AXIS
                    if(y<255) {
                        if (is_transparent(chunk->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z + ChunkGovernor::CHUNK_HEIGHT].blockType)) {
                            masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Top;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Top;
                        (*face_count)++;
                    }
                    if(y>1){
                        if (is_transparent(chunk->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z - ChunkGovernor::CHUNK_HEIGHT].blockType)) {
                            masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Bottom;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Bottom;
                        (*face_count)++;
                    }
                }
            }
        }
        return masks;
    }