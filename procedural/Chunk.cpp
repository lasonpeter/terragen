//
// Created by xenu on 06/05/2025.
//

#include "Chunk.h"

#include "ChunkGovernor.h"
#include "../utilities/FaceMask.h"

void Chunk::generateChunkFaceMasks(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks) {


    for (int i=0; i<ChunkGovernor::CHUNK_SIZE; i++) {
        for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
            for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                if(is_transparent((chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]).blockType)){
                    continue;
                }
                //ON Z AXIS
                if(z<15) {
                    if (is_transparent((chunk->blocks[chunk_index *ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + 1]).blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Front;
                        (*face_count)++;
                    }
                }
                else{
                    //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                    /*chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Front;
                    (*face_count)++;*/
                }
                if(z>1){
                    if (is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z - 1].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Back;
                        (*face_count)++;
                    }
                }else{
                    //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                    /*chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Back;
                    (*face_count)++;*/
                }
                //ON X AXIS
                if(x<15) {
                    if (is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + ChunkGovernor::CHUNK_SIZE].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Right;
                        (*face_count)++;
                    }
                }
                else{
                    //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                    /*chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Right;
                    (*face_count)++;*/
                }
                if(x>1){
                    if (is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z - ChunkGovernor::CHUNK_SIZE].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Left;
                        (*face_count)++;
                    }
                }else{
                    //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                    /*chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Left;
                    (*face_count)++;*/
                }
                //ON Y AXIS
                if(chunk_index*16<255) {
                    if (is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + ChunkGovernor::CHUNK_HEIGHT].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Top;
                        (*face_count)++;
                    }
                }
                else{
                    //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                    /*chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Top;
                    (*face_count)++;*/
                }
                if(chunk_index>1){
                    if (is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z - ChunkGovernor::CHUNK_HEIGHT].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Bottom;
                        (*face_count)++;
                    }
                }else{
                    //LETS ASSUME FOR NOW THAT THOSE WILL ALSO BE RENDERED
                    /*chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]+=FaceMask::Bottom;
                    (*face_count)++;*/
                }
            }
        }
    }

    }