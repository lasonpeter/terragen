//
// Created by xenu on 06/05/2025.
//

#include "Chunk.h"

#include "ChunkGovernor.h"
#include "../utilities/FaceMask.h"
uint8_t *Chunk::generateChunkFaceMasks(Chunk *chunk,int* face_count,int chunkIndex) {
        auto* masks = new uint8_t[ChunkGovernor::CHUNK_SIZE * ChunkGovernor::CHUNK_SIZE * ChunkGovernor::CHUNK_SIZE]{};
        for (int y = 0; y < ChunkGovernor::CHUNK_SIZE; ++y) {
            for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
                for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                    if(is_transparent((chunk->blocks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]).blockType)){
                        continue;
                    }
                    //ON Z AXIS
                    if(z<ChunkGovernor::CHUNK_SIZE-1) {
                        if (is_transparent((chunk->blocks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + 1]).blockType)) {
                            masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Front;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Front;
                        (*face_count)++;
                    }
                    if(z>1){
                        if (is_transparent(chunk->blocks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z - 1].blockType)) {
                            masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Back;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Back;
                        (*face_count)++;
                    }
                    //ON X AXIS
                    if(x<ChunkGovernor::CHUNK_SIZE -1) {
                        if (is_transparent(chunk->blocks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + ChunkGovernor::CHUNK_SIZE].blockType)) {
                            masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Right;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Right;
                        (*face_count)++;
                    }
                    if(x>1){
                        if (is_transparent(chunk->blocks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z - ChunkGovernor::CHUNK_SIZE].blockType)) {
                            masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Left;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Left;
                        (*face_count)++;
                    }
                    //ON Y AXIS
                    if(y<ChunkGovernor::CHUNK_SIZE-1) {
                        if (is_transparent(chunk->blocks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + ChunkGovernor::CHUNK_HEIGHT].blockType)) {
                            masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Top;
                            (*face_count)++;
                        }
                    }
                    else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        if(!is_transparent(chunk->blocks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + ChunkGovernor::CHUNK_HEIGHT].blockType)) {
                            masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Top;
                            (*face_count)++;
                        }
                    }
                    if(y>1){
                        if (is_transparent(chunk->blocks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z - ChunkGovernor::CHUNK_HEIGHT].blockType)) {
                            masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Bottom;
                            (*face_count)++;
                        }
                    }else{
                        //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                        masks[chunkIndex*ChunkGovernor::CHUNK_SIZE + y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Bottom;
                        (*face_count)++;
                    }
                }
            }
        }
        return masks;
    }