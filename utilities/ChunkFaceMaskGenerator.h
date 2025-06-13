//
// Created by Amazon Q on 12/06/2025.
//

#ifndef TERRAGEN_CHUNKFACEMASKGENERATOR_H
#define TERRAGEN_CHUNKFACEMASKGENERATOR_H

#include <cstdint>
#include "../procedural/Chunk.h"
#include "FaceMask.h"

// Constants from ChunkGovernor to avoid dependency
namespace ChunkConstants {
    constexpr int CHUNK_SIZE = 16;
    constexpr int CHUNK_HEIGHT = 256;
    constexpr int SUB_CHUNK_SIZE = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
    constexpr int CHUNK_SLICE_SIZE = CHUNK_SIZE * CHUNK_SIZE;
}

class ChunkFaceMaskGenerator {
public:
    /**
     * Generates face masks for a chunk without using ChunkGovernor
     * 
     * @param chunk The chunk to generate face masks for
     * @param face_count Pointer to count of faces (will be incremented)
     * @param chunk_index The index of the sub-chunk
     * @param chunkFaceMasks Array to store the face masks
     */
    static void generateFaceMasks(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks) {
        // Call the more detailed version with null neighbors
        generateFaceMasksWithNeighbors(chunk, face_count, chunk_index, chunkFaceMasks, nullptr, nullptr, nullptr, nullptr);
    }

    /**
     * Generates face masks for a chunk with neighbor information without using ChunkGovernor
     * 
     * @param chunk The chunk to generate face masks for
     * @param face_count Pointer to count of faces (will be incremented)
     * @param chunk_index The index of the sub-chunk
     * @param chunkFaceMasks Array to store the face masks
     * @param chunkLeft The chunk to the left (X-)
     * @param chunkRight The chunk to the right (X+)
     * @param chunkFront The chunk to the front (Z+)
     * @param chunkBack The chunk to the back (Z-)
     */
    static void generateFaceMasksWithNeighbors(const Chunk *chunk, int *face_count, int chunk_index, uint8_t *chunkFaceMasks,
                                              const Chunk *chunkLeft, const Chunk *chunkRight, 
                                              const Chunk *chunkFront, const Chunk *chunkBack) {
        for (int i = 0; i < ChunkConstants::CHUNK_SIZE; i++) {
            for (int x = 0; x < ChunkConstants::CHUNK_SIZE; ++x) {
                for (int z = 0; z < ChunkConstants::CHUNK_SIZE; ++z) {
                    if(is_transparent((chunk->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z]).blockType)){
                        continue;
                    }

                    // Back face (Z-)
                    if(z == 0) {
                        // Edge of chunk - check neighboring chunk if available
                        if(chunkBack != nullptr) {
                            // Check the last block in the back chunk
                            if(is_transparent(chunkBack->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + (ChunkConstants::CHUNK_SIZE-1)].blockType)) {
                                chunkFaceMasks[i * ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Back;
                                (*face_count)++;
                            }
                        } else {
                            // No neighbor, render the face
                            chunkFaceMasks[i * ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Back;
                            (*face_count)++;
                        }
                    } else if(is_transparent(chunk->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z - 1].blockType)) {
                        chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Back;
                        (*face_count)++;
                    }

                    // Front face (Z+)
                    if(z == ChunkConstants::CHUNK_SIZE - 1) {
                        // Edge of chunk - check neighboring chunk if available
                        if(chunkFront != nullptr) {
                            // Check the first block in the front chunk
                            if(is_transparent(chunkFront->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + 0].blockType)) {
                                chunkFaceMasks[i * ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Front;
                                (*face_count)++;
                            }
                        } else {
                            // No neighbor, render the face
                            chunkFaceMasks[i * ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Front;
                            (*face_count)++;
                        }
                    } else if(is_transparent(chunk->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z + 1].blockType)) {
                        chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Front;
                        (*face_count)++;
                    }

                    // Right face (X+)
                    if(x == ChunkConstants::CHUNK_SIZE - 1) {
                        // Edge of chunk - check neighboring chunk if available
                        if(chunkRight != nullptr) {
                            // Check the first block in the right chunk
                            if(is_transparent(chunkRight->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + 0 * ChunkConstants::CHUNK_SIZE + z].blockType)) {
                                chunkFaceMasks[i * ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Right;
                                (*face_count)++;
                            }
                        } else {
                            // No neighbor, render the face
                            chunkFaceMasks[i * ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Right;
                            (*face_count)++;
                        }
                    } else if(is_transparent(chunk->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + (x + 1) * ChunkConstants::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Right;
                        (*face_count)++;
                    }

                    // Left face (X-)
                    if(x == 0) {
                        // Edge of chunk - check neighboring chunk if available
                        if(chunkLeft != nullptr) {
                            // Check the last block in the left chunk
                            if(is_transparent(chunkLeft->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + (ChunkConstants::CHUNK_SIZE-1) * ChunkConstants::CHUNK_SIZE + z].blockType)) {
                                chunkFaceMasks[i * ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Left;
                                (*face_count)++;
                            }
                        } else {
                            // No neighbor, render the face
                            chunkFaceMasks[i * ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Left;
                            (*face_count)++;
                        }
                    } else if(is_transparent(chunk->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + i*ChunkConstants::CHUNK_SLICE_SIZE + (x - 1) * ChunkConstants::CHUNK_SIZE + z].blockType)) {
                        chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Left;
                        (*face_count)++;
                    }

                    // Top face (Y+)
                    if(i == ChunkConstants::CHUNK_SIZE - 1 && chunk_index < 15) {
                        // Check the block in the next sub-chunk above
                        if(is_transparent(chunk->blocks[(chunk_index+1) * ChunkConstants::SUB_CHUNK_SIZE + 0*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z].blockType)) {
                            chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Top;
                            (*face_count)++;
                        }
                    } else if(i < ChunkConstants::CHUNK_SIZE - 1) {
                        if(is_transparent(chunk->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + (i+1)*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z].blockType)) {
                            chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Top;
                            (*face_count)++;
                        }
                    } else {
                        // Top of the world, always render
                        chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Top;
                        (*face_count)++;
                    }

                    // Bottom face (Y-)
                    if(i == 0 && chunk_index > 0) {
                        // Check the block in the next sub-chunk below
                        if(is_transparent(chunk->blocks[(chunk_index-1) * ChunkConstants::SUB_CHUNK_SIZE + (ChunkConstants::CHUNK_SIZE-1)*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z].blockType)) {
                            chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Bottom;
                            (*face_count)++;
                        }
                    } else if(i > 0) {
                        if(is_transparent(chunk->blocks[chunk_index * ChunkConstants::SUB_CHUNK_SIZE + (i-1)*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z].blockType)) {
                            chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Bottom;
                            (*face_count)++;
                        }
                    } else if(chunk_index == 0) {
                        // Bottom of the world, always render
                        chunkFaceMasks[i*ChunkConstants::CHUNK_SLICE_SIZE + x * ChunkConstants::CHUNK_SIZE + z] += FaceMask::Bottom;
                        (*face_count)++;
                    }
                }
            }
        }
    }
};

#endif //TERRAGEN_CHUNKFACEMASKGENERATOR_H