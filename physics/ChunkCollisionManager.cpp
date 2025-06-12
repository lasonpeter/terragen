//
// Created by Amazon Q on 12/06/2025.
//

#include "ChunkCollisionManager.h"
#include <iostream>

ChunkCollisionManager::ChunkCollisionManager(ChunkGovernor* governor, Player* playerObj) 
    : chunkGovernor(governor), player(playerObj) {
}

Int2 ChunkCollisionManager::GetChunkPositionFromWorldPos(const Vector3& position) {
    // Convert world position to chunk coordinates
    int chunkX = static_cast<int>(floor(position.x / ChunkGovernor::CHUNK_SIZE));
    int chunkZ = static_cast<int>(floor(position.z / ChunkGovernor::CHUNK_SIZE));
    return {chunkX, chunkZ};
}

Chunk* ChunkCollisionManager::GetChunkAtPosition(const Int2& chunkPos) {
    // Find chunk at the given position
    for (auto* chunk : chunkGovernor->chunks_) {
        if (chunk->position.x == chunkPos.x && chunk->position.y == chunkPos.y) {
            return chunk;
        }
    }
    return nullptr;
}

void ChunkCollisionManager::UpdateCollisions(float deltaTime) {
    // Get player position from RigidBody component
    auto* rigidBody = player->GetComponent<ECBS::RigidBody>();
    auto* collider = player->GetComponent<ECBS::Collider>();
    
    if (!rigidBody || !collider) {
        return;
    }
    
    // Get player's position from the bounding box center
    Vector3 playerPos = {
        (collider->boundingBox.min.x + collider->boundingBox.max.x) / 2.0f,
        (collider->boundingBox.min.y + collider->boundingBox.max.y) / 2.0f,
        (collider->boundingBox.min.z + collider->boundingBox.max.z) / 2.0f
    };
    
    // Get the chunk position from player's world position
    Int2 currentChunkPos = GetChunkPositionFromWorldPos(playerPos);
    
    // Get current chunk and adjacent chunks
    Chunk* currentChunk = GetChunkAtPosition(currentChunkPos);
    Chunk* leftChunk = GetChunkAtPosition({currentChunkPos.x - 1, currentChunkPos.y});
    Chunk* rightChunk = GetChunkAtPosition({currentChunkPos.x + 1, currentChunkPos.y});
    Chunk* frontChunk = GetChunkAtPosition({currentChunkPos.x, currentChunkPos.y + 1});
    Chunk* backChunk = GetChunkAtPosition({currentChunkPos.x, currentChunkPos.y - 1});
    
    // Process collisions for current chunk and adjacent chunks
    if (currentChunk) {
        // Process collision with current chunk
        // This would involve checking against blocks in the chunk
        // For now, just log that we're checking this chunk
        std::cout << "Checking collisions in chunk: [" << currentChunkPos.x << ", " << currentChunkPos.y << "]" << std::endl;


        // Now we have the face masks for collision detection
        // We would use these to check for collisions with the player
        // This is a placeholder for the actual collision detection logic
    }
}