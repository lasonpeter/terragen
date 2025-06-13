//
// Created by xenu on 12/06/2025.
//

#include <iostream>
#include <thread>
#include "ChunkCache.h"
#include "../rendering/StaticRenderer.h"
#include "../rendering/chunks/ChunkRenderer.h"
#include "../procedural/ChunkGovernor.h"




void ChunkCache::loadMesh(Chunk* chunk) {
    // Check if we already have this chunk
    std::string chunkKey = Int2ToString(chunk->position);
    if (chunkMeshesCache.contains(chunkKey)) {
        return; // Already have this chunk
    }
    
    // Check if we already have a pending mesh generation for this chunk
    if (pendingMeshes.contains(chunkKey)) {
        return; // Already being processed
    }

    // Find neighboring chunks if they exist
    Chunk* chunkLeft = nullptr;
    Chunk* chunkRight = nullptr;
    Chunk* chunkFront = nullptr;
    Chunk* chunkBack = nullptr;

    // In your project, x and z are switched, so adjust accordingly
    // Check for left neighbor (y-1 in your coordinate system)
    Int2 leftPos = {chunk->position.x, chunk->position.y - 1};
    chunkLeft = getChunk(leftPos);

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

    // Start async mesh generation
    std::future<ChunkMesh*> meshFuture = meshThreadPool.enqueue(
        &ChunkCache::generateMeshAsync, this, chunk, chunkLeft, chunkRight, chunkFront, chunkBack);
    
    // Store the future for later checking
    pendingMeshes[chunkKey] = std::move(meshFuture);
}

ChunkMesh* ChunkCache::generateMeshAsync(Chunk* chunk, const Chunk* chunkLeft, const Chunk* chunkRight, 
                                       const Chunk* chunkFront, const Chunk* chunkBack) {
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

    chunk_mesh->chunkPosition = chunk->position;
    return chunk_mesh;
}

void ChunkCache::updatePendingMeshes() {
    std::vector<std::string> completedMeshes;
    
    // Check for completed mesh generations
    for (auto& [chunkKey, future] : pendingMeshes) {
        // Check if the future is ready without blocking
        if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            // Get the completed mesh
            ChunkMesh* chunkMesh = future.get();
            
            // Store the mesh in the cache
            chunkMeshesCache[chunkKey] = chunkMesh;
            
            // Upload meshes to GPU (must be done on main thread)
            for (auto& mesh : chunkMesh->meshes) {
                UploadMesh(&mesh.mesh, true);
            }
            
            // Mark this mesh as completed
            completedMeshes.push_back(chunkKey);
        }
    }
    
    // Remove completed meshes from pending list
    for (const auto& key : completedMeshes) {
        pendingMeshes.erase(key);
    }
}

void ChunkCache::loadChunk(Chunk* chunk) {
    auto chunkKey = Int2ToString(chunk->position);
    if (chunkCache.contains(chunkKey)) {
        throw std::invalid_argument("Chunk already exist");
    }
    chunkCache.insert({Int2ToString(chunk->position), chunk});
}

void ChunkCache::addChunk(Chunk *chunk) {
    auto chunkKey = Int2ToString(chunk->position);
    if (chunkCache.contains(chunkKey)) {
        throw std::invalid_argument("Chunk already exist");
    }
    loadChunk(chunk);
    loadMesh(chunk);

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
    if (chunkLeft != nullptr)
        regenerateChunkMesh(chunkLeft);
    if (chunkRight != nullptr)
        regenerateChunkMesh(chunkRight);
    if (chunkFront != nullptr)
        regenerateChunkMesh(chunkFront);
    if (chunkBack != nullptr)
        regenerateChunkMesh(chunkBack);
}

void ChunkCache::regenerateChunkMesh(Chunk* chunk) {
    auto chunkKey = Int2ToString(chunk->position);
    if (!chunkCache.contains(chunkKey)) {
        throw std::invalid_argument("Chunk does not exist");
    }
    
    // If there's a pending mesh generation for this chunk, wait for it to complete
    if (pendingMeshes.contains(chunkKey)) {
        pendingMeshes[chunkKey].wait(); // Wait for the current task to finish
        pendingMeshes.erase(chunkKey);  // Remove it from pending
    }
    
    unloadMesh(chunk->position);
    loadMesh(chunk);
}

void ChunkCache::removeChunk(Int2 chunkPosition) {
    std::string chunkKey = Int2ToString(chunkPosition);
    
    // If there's a pending mesh generation for this chunk, wait for it to complete
    if (pendingMeshes.contains(chunkKey)) {
        pendingMeshes.erase(chunkKey);  // Remove it from pending without waiting
    }
    
    unloadChunk(chunkPosition);
    unloadMesh(chunkPosition);
}

void ChunkCache::unloadChunk(Int2 chunkPosition) {
    std::string chunkKey = Int2ToString(chunkPosition);
    if (chunkCache.find(chunkKey) != chunkCache.end()) {
        delete chunkCache.at(chunkKey);
    }
}

void ChunkCache::unloadMesh(Int2 chunkPosition) {
    std::string chunkKey = Int2ToString(chunkPosition);

    // Check if there's a pending mesh generation for this chunk
    if (pendingMeshes.find(chunkKey) != pendingMeshes.end()) {
        // Cancel the pending mesh generation by removing it from the map
        // Note: The task will still complete in the thread pool, but we'll ignore the result
        pendingMeshes.erase(chunkKey);
    }

    // We now need to properly unload the meshes
    if (chunkMeshesCache.find(chunkKey) != chunkMeshesCache.end()) {
        ChunkMesh* chunkMesh = chunkMeshesCache.at(chunkKey);
        
        for (auto & mesh : chunkMesh->meshes) {
            // sleep for 50 ms to avoid memory corruption
            std::this_thread::sleep_for(std::chrono::nanoseconds (1));
            // Only unload meshes that have been properly initialized
            if (mesh.mesh.vaoId > 0 &&
                mesh.mesh.vertexCount > 0) {
                UnloadMesh(mesh.mesh);
                delete[] mesh.chunkFaceMasks;
                }
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
