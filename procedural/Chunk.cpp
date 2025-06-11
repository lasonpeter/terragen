//
// Created by xenu on 06/05/2025.
//

#include "Chunk.h"

#include <iostream>
#include <ostream>

#include "ChunkGovernor.h"
#include "../utilities/FaceMask.h"


void Chunk::generateChunkFaceMasks(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks, int chunk_index_x, int chunk_index_z, std::vector<Chunk*> *chunks, int renderDistance, int chunkPosX,int chunkPosZ) {
    //TODO FIX THIS PROPERLY
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; i++) {
        for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
            for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                if(is_transparent((chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]).blockType)){
                    continue;
                }


                if(z==0){
                    if (chunkPosZ >0 && is_transparent(chunks->at(chunkPosX * renderDistance + chunkPosZ -1)->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + ChunkGovernor::CHUNK_SIZE].blockType)){
                            chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z] += FaceMask::Back;
                            (*face_count)++;
                        }
                    chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z] += FaceMask::Back;
                    (*face_count)++;
                }else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z -1].blockType)) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Back;
                    (*face_count)++;
                }


                // Front face (Z+)
                if(z == ChunkGovernor::CHUNK_SIZE - 1) {
                    if (chunkPosZ <renderDistance-1 && is_transparent(chunks->at(chunkPosX * renderDistance + chunkPosZ +1)->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + ChunkGovernor::CHUNK_SIZE].blockType)){
                        chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z] += FaceMask::Front;
                        (*face_count)++;
                    }
                    chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z] += FaceMask::Front;
                    (*face_count)++;
                } else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + 1].blockType)) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Front;
                    (*face_count)++;
                }

                try
                {
                    if(x == ChunkGovernor::CHUNK_SIZE - 1) {
                        // Check neighboring chunk
                        if( chunkPosX < renderDistance -1 && is_transparent(chunks->at((chunk_index_x + 1) * renderDistance + chunk_index_z)->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + (x+1)* ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                            chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Right;
                            (*face_count)++;
                        }
                        chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z] += FaceMask::Right;
                        (*face_count)++;
                    }
                    else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + (x + 1) * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Right;
                        (*face_count)++;
                    }
                }
                catch (_exception e)
                {
                    std::cerr << "Exception!" << std::endl;
                }
                // Right face (X+)


                // LEFT face (X-)
                if(x == 0) {
                    // Check neighboring chunk
                    if( chunkPosX >0 && is_transparent(chunks->at((chunk_index_x - 1) * renderDistance + chunk_index_z)->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + (x+1)* ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Left;
                        (*face_count)++;
                    }
                    chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z] += FaceMask::Left;
                    (*face_count)++;
                }
                else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + (x - 1) * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Left;
                    (*face_count)++;
                }

                // Top face (Y+)
                if(chunk_index < 16) {
                    if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + (i+1)*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Top;
                        (*face_count)++;
                    }
                }

                // Bottom face (Y-)
                if(chunk_index == 0) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Bottom;
                    (*face_count)++;
                } else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + (i-1)*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Bottom;
                    (*face_count)++;
                }
            }
        }
    }
}