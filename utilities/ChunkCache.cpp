//
// Created by xenu on 12/06/2025.
//

#include <iostream>
#include <thread>
#include "ChunkCache.h"
#include "../rendering/StaticRenderer.h"
#include "../rendering/chunks/ChunkRenderer.h"
#include "../procedural/ChunkGovernor.h"




void ChunkCache::addChunk(Chunk *chunk) {
    // Check if we already have this chunk
    std::string chunkKey = Int2ToString(chunk->position);
    if (chunkMeshesCache.find(chunkKey) != chunkMeshesCache.end()) {
        return; // Already have this chunk
    }
    
    // Find neighboring chunks if they exist
    Chunk* chunkLeft = nullptr;
    Chunk* chunkRight = nullptr;
    Chunk* chunkFront = nullptr;
    Chunk* chunkBack = nullptr;
    
    // In your project, x and z are switched, so adjust accordingly
    // Check for left neighbor (y-1 in your coordinate system)
    Int2 leftPos = {chunk->position.x, chunk->position.y - 1};
    chunkLeft= getChunk(leftPos);
    
    // Check for right neighbor (y+1 in your coordinate system)
    Int2 rightPos = {chunk->position.x, chunk->position.y + 1};
    chunkRight = getChunk(rightPos);
    
    // Check for back neighbor (x-1 in your coordinate system)
    Int2 backPos = {chunk->position.x - 1, chunk->position.y};
    chunkBack = getChunk(backPos);
    
    // Check for front neighbor (x+1 in your coordinate system)
    Int2 frontPos = {chunk->position.x + 1, chunk->position.y};
    chunkFront = getChunk(frontPos);
    
    // Debug output to verify neighbors were found
    std::cout << "Chunk at (" << chunk->position.x << "," << chunk->position.y << ") has neighbors: ";
    std::cout << "Left: " << (chunkLeft ? "Yes" : "No") << ", ";
    std::cout << "Right: " << (chunkRight ? "Yes" : "No") << ", ";
    std::cout << "Front: " << (chunkFront ? "Yes" : "No") << ", ";
    std::cout << "Back: " << (chunkBack ? "Yes" : "No") << std::endl;
    
    ChunkMesh *chunk_mesh = new ChunkMesh{};
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
        int face_count{};
        SubChunkMesh chunkMesh = SubChunkMesh();
        int *amount_of_faces = new int;
        *amount_of_faces = 0;
        
        // Generate face masks considering neighboring chunks
        Chunk::generateChunkFaceMasksWithNeighbors(chunk, amount_of_faces, i, chunkMesh.chunkFaceMasks,
                                                  chunkLeft, chunkRight, chunkFront, chunkBack);
        Mesh mesh = {0};
        mesh.triangleCount = (*amount_of_faces) * 2;
        mesh.vertexCount = (*amount_of_faces) * 4;
        mesh.vertices = new float[mesh.vertexCount * 3];    // 3 vertices, 3 coordinates each (x, y, z)
        mesh.texcoords = new float[mesh.vertexCount * 2];   // 3 vertices, 2 coordinates each (x, y)
        mesh.normals = new float[mesh.vertexCount * 3];     // 3 vertices, 3 coordinates each (x, y, z)
        mesh.indices = new unsigned short[mesh.triangleCount * 3];
        for (int y = 0; y < ChunkGovernor::CHUNK_SIZE; ++y) {
            for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
                for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                    if (is_transparent(chunk->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType)) {
                        continue;
                    }
                    face_count = StaticRenderer::RenderCube(
                            chunkMesh.chunkFaceMasks[y * ChunkGovernor::CHUNK_HEIGHT +
                                                     x * ChunkGovernor::CHUNK_SIZE + z], mesh.vertices,
                            mesh.indices, mesh.texcoords, mesh.normals, new Int3{x, y, z}, face_count, chunk->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType);
                }
            }
        }

        for (int z = 0; z <= mesh.vertexCount; z = z + 3) {
            mesh.normals[z] = 0;
            mesh.normals[z + 1] = 1;
            mesh.normals[z + 2] = 0;
        }
        chunkMesh.mesh = mesh;
        chunk_mesh->meshes[i] = chunkMesh;
    }

    chunkCache.insert({Int2ToString(chunk->position), chunk});

    chunk_mesh->chunkPosition = chunk->position;
    chunkMeshesCache.insert({Int2ToString(chunk->position),chunk_mesh});

    //UPLOADS MESHES OF A CHUNK TO GPU
    for (auto& mesh: chunkMeshesCache.at(Int2ToString(chunk->position))->meshes) {
        UploadMesh(&mesh.mesh, true);
    }

    // We no longer need to create models since we'll be using DrawMesh directly
    // Just ensure the meshes are properly uploaded to GPU
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
        // Make sure the mesh is uploaded to GPU
        if (!chunkMeshesCache.at(Int2ToString(chunk->position))->meshes[i].mesh.vaoId) {
            UploadMesh(&chunkMeshesCache.at(Int2ToString(chunk->position))->meshes[i].mesh, true);
        }
    }
}
void ChunkCache::removeChunk(Int2 chunkPosition) {
    std::string chunkKey = Int2ToString(chunkPosition);
    
    // We now need to properly unload the meshes
    if (chunkMeshesCache.find(chunkKey) != chunkMeshesCache.end()) {
        ChunkMesh* chunkMesh = chunkMeshesCache.at(chunkKey);

        // Only unload a limited number of meshes to avoid memory corruption
        // Based on your observation, keeping it under 7
        
        for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; i++) {
            // sleep for 50 ms to avoid memory corruption
            std::this_thread::sleep_for(std::chrono::nanoseconds (1));
            // Only unload meshes that have been properly initialized
            if (chunkMesh->meshes[i].mesh.vaoId > 0 && 
                chunkMesh->meshes[i].mesh.vertexCount > 0) {
                UnloadMesh(chunkMesh->meshes[i].mesh);
                delete[] chunkMesh->meshes[i].chunkFaceMasks;
            }
        }

        //remove chunk from cache
        if (chunkCache.find(chunkKey) != chunkCache.end()) {
            chunkCache.erase(chunkKey);
        }

        // Delete the ChunkMesh object itself
        delete chunkMesh;
        chunkMeshesCache.erase(chunkKey);
    }
}

ChunkMesh *ChunkCache::getChunkMesh(Int2 chunkPosition) {
    return nullptr;
}

// ChunkModel method removed as we no longer use Models

std::string ChunkCache::Int2ToString(Int2 int2) {
    return std::to_string(int2.x) + "_" + std::to_string(int2.y);
}

Chunk *ChunkCache::getChunk(Int2 chunkPosition) {
    std::string chunkKey = Int2ToString(chunkPosition);
    if (chunkCache.find(chunkKey) != chunkCache.end()) {
        return chunkCache.at(chunkKey);
    }else{
        return nullptr;
    }
}
