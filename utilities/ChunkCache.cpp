//
// Created by xenu on 12/06/2025.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip> // For std::setprecision
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
    auto start = std::chrono::high_resolution_clock::now();
    std::string chunkKey = Int2ToString(chunk->position);
    
    ChunkMesh *chunk_mesh = new ChunkMesh{};
    
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
        auto subchunkStart = std::chrono::high_resolution_clock::now();
        int face_count{};
        SubChunkMesh chunkMesh = SubChunkMesh();
        int *amount_of_faces = new int;
        *amount_of_faces = 0;

        // Generate face masks considering neighboring chunks
        auto faceMaskStart = std::chrono::high_resolution_clock::now();
        Chunk::generateChunkFaceMasksWithNeighbors(chunk, amount_of_faces, i, chunkMesh.chunkFaceMasks,
                                                  chunkLeft, chunkRight, chunkFront, chunkBack);
        auto faceMaskEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> faceMaskTime = faceMaskEnd - faceMaskStart;
        
        Mesh mesh = {0};
        mesh.triangleCount = (*amount_of_faces) * 2;
        mesh.vertexCount = (*amount_of_faces) * 4;
        mesh.vertices = new float[mesh.vertexCount * 3];    // 3 vertices, 3 coordinates each (x, y, z)
        mesh.texcoords = new float[mesh.vertexCount * 2];   // 3 vertices, 2 coordinates each (x, y)
        mesh.normals = new float[mesh.vertexCount * 3];     // 3 vertices, 3 coordinates each (x, y, z)
        mesh.indices = new unsigned short[mesh.triangleCount * 3];
        
        auto renderStart = std::chrono::high_resolution_clock::now();
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
        auto renderEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> renderTime = renderEnd - renderStart;

        for (int z = 0; z <= mesh.vertexCount; z = z + 3) {
            mesh.normals[z] = 0;
            mesh.normals[z + 1] = 1;
            mesh.normals[z + 2] = 0;
        }
        
        chunkMesh.mesh = mesh;
        chunk_mesh->meshes[i] = chunkMesh;
        
        auto subchunkEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> subchunkTime = subchunkEnd - subchunkStart;
        
        if (i == 0) { // Only log for the first subchunk to avoid spam
            std::cout << "Chunk " << chunkKey << " subchunk " << i << " times:" << std::endl;
            std::cout << "  Face mask generation: " << faceMaskTime.count() << "ms" << std::endl;
            std::cout << "  Cube rendering: " << renderTime.count() << "ms" << std::endl;
            std::cout << "  Total subchunk time: " << subchunkTime.count() << "ms" << std::endl;
        }
    }

    chunk_mesh->chunkPosition = chunk->position;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> totalTime = end - start;
    std::cout << "Total mesh generation time for chunk " << chunkKey << ": " << totalTime.count() << "ms" << std::endl;
    
    return chunk_mesh;
}

void ChunkCache::updatePendingMeshes() {
    std::vector<std::string> completedMeshes;
    int uploadedCount = 0;
    
    // Limit the number of meshes processed per frame to avoid stuttering
    const int MAX_MESHES_PER_FRAME = 4;
    int processedCount = 0;
    
    // Check for completed mesh generations
    for (auto& [chunkKey, future] : pendingMeshes) {
        // Check if the future is ready without blocking
        if (future.wait_for(std::chrono::nanoseconds(1)) == std::future_status::ready) {
            // Get the completed mesh
            ChunkMesh* chunkMesh = future.get();
            
            // Store the mesh in the cache
            chunkMeshesCache[chunkKey] = chunkMesh;
            
            // Upload meshes to GPU (must be done on main thread)
            for (auto& mesh : chunkMesh->meshes) {
                UploadMesh(&mesh.mesh, true);
                uploadedCount++;
            }
            
            // Mark this mesh as completed
            completedMeshes.push_back(chunkKey);
            
            // Limit processing to avoid frame stuttering
            processedCount++;
            if (processedCount >= MAX_MESHES_PER_FRAME) {
                break;
            }
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
    
    // Instead of regenerating all neighbors immediately, queue them for later regeneration
    // This spreads out the work across multiple frames
    if (chunkLeft != nullptr)
        loadMesh(chunkLeft);
    if (chunkRight != nullptr)
        loadMesh(chunkRight);
    if (chunkFront != nullptr)
        loadMesh(chunkFront);
    if (chunkBack != nullptr)
        loadMesh(chunkBack);
}

void ChunkCache::regenerateChunkMesh(Chunk* chunk) {
    auto chunkKey = Int2ToString(chunk->position);
    if (!chunkCache.contains(chunkKey)) {
        throw std::invalid_argument("Chunk does not exist");
    }
    
    // If there's a pending mesh generation for this chunk, cancel it instead of waiting
    if (pendingMeshes.contains(chunkKey)) {
        pendingMeshes.erase(chunkKey);  // Remove it from pending without waiting
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
        pendingMeshes.erase(chunkKey);
    }

    // We now need to properly unload the meshes
    if (chunkMeshesCache.find(chunkKey) != chunkMeshesCache.end()) {
        ChunkMesh* chunkMesh = chunkMeshesCache.at(chunkKey);
        
        for (auto & mesh : chunkMesh->meshes) {
            // Remove the sleep that was causing stuttering
            
            // Only unload meshes that have been properly initialized
            if (mesh.mesh.vaoId > 0 && mesh.mesh.vertexCount > 0) {
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
