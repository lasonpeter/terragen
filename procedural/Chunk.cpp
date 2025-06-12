//
// Created by xenu on 06/05/2025.
//

#include "Chunk.h"

#include "ChunkGovernor.h"
#include "../utilities/FaceMask.h"


void Chunk::generateChunkFaceMasks(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks) {
    // Call the more detailed version with null neighbors
    generateChunkFaceMasksWithNeighbors(chunk, face_count, chunk_index, chunkFaceMasks, nullptr, nullptr, nullptr, nullptr);
}

void Chunk::generateChunkFaceMasksWithNeighbors(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks,
                                               const Chunk *chunkLeft, const Chunk *chunkRight, 
                                               const Chunk *chunkFront, const Chunk *chunkBack) {
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; i++) {
        for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
            for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                if(is_transparent((chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z]).blockType)){
                    continue;
                }

                // Back face (Z-)
                if(z == 0) {
                    // Edge of chunk - check neighboring chunk if available
                    if(chunkBack != nullptr) {
                        // Check the last block in the back chunk (accounting for x/z swap)
                        if(is_transparent(chunkBack->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + (ChunkGovernor::CHUNK_SIZE-1)].blockType)) {
                            chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Back;
                            (*face_count)++;
                        }
                    } else {
                        // No neighbor, render the face
                        chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Back;
                        (*face_count)++;
                    }
                } else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z - 1].blockType)) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Back;
                    (*face_count)++;
                }

                // Front face (Z+)
                if(z == ChunkGovernor::CHUNK_SIZE - 1) {
                    // Edge of chunk - check neighboring chunk if available
                    if(chunkFront != nullptr) {
                        // Check the first block in the front chunk (accounting for x/z swap)
                        if(is_transparent(chunkFront->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + 0].blockType)) {
                            chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Front;
                            (*face_count)++;
                        }
                    } else {
                        // No neighbor, render the face
                        chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Front;
                        (*face_count)++;
                    }
                } else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z + 1].blockType)) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Front;
                    (*face_count)++;
                }

                // Right face (X+)
                if(x == ChunkGovernor::CHUNK_SIZE - 1) {
                    // Edge of chunk - check neighboring chunk if available
                    if(chunkRight != nullptr) {
                        // Check the first block in the right chunk (accounting for x/z swap)
                        if(is_transparent(chunkRight->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + 0 * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                            chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Right;
                            (*face_count)++;
                        }
                    } else {
                        // No neighbor, render the face
                        chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Right;
                        (*face_count)++;
                    }
                } else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + (x + 1) * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Right;
                    (*face_count)++;
                }

                // LEFT face (X-)
                if(x == 0) {
                    // Edge of chunk - check neighboring chunk if available
                    if(chunkLeft != nullptr) {
                        // Check the last block in the left chunk (accounting for x/z swap)
                        if(is_transparent(chunkLeft->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + (ChunkGovernor::CHUNK_SIZE-1) * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                            chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Left;
                            (*face_count)++;
                        }
                    } else {
                        // No neighbor, render the face
                        chunkFaceMasks[i * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Left;
                        (*face_count)++;
                    }
                } else if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + i*ChunkGovernor::CHUNK_SLICE_SIZE + (x - 1) * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Left;
                    (*face_count)++;
                }

                // Top face (Y+)
                if(i == ChunkGovernor::CHUNK_SIZE - 1 && chunk_index < 15) {
                    // Check the block in the next sub-chunk above
                    if(is_transparent(chunk->blocks[(chunk_index+1) * ChunkGovernor::SUB_CHUNK_SIZE + 0*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Top;
                        (*face_count)++;
                    }
                } else if(i < ChunkGovernor::CHUNK_SIZE - 1) {
                    if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + (i+1)*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Top;
                        (*face_count)++;
                    }
                } else {
                    // Top of the world, always render
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Top;
                    (*face_count)++;
                }

                // Bottom face (Y-)
                if(i == 0 && chunk_index > 0) {
                    // Check the block in the next sub-chunk below
                    if(is_transparent(chunk->blocks[(chunk_index-1) * ChunkGovernor::SUB_CHUNK_SIZE + (ChunkGovernor::CHUNK_SIZE-1)*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Bottom;
                        (*face_count)++;
                    }
                } else if(i > 0) {
                    if(is_transparent(chunk->blocks[chunk_index * ChunkGovernor::SUB_CHUNK_SIZE + (i-1)*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Bottom;
                        (*face_count)++;
                    }
                } else if(chunk_index == 0) {
                    // Bottom of the world, always render
                    chunkFaceMasks[i*ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE + z] += FaceMask::Bottom;
                    (*face_count)++;
                }
            }
        }
    }
}