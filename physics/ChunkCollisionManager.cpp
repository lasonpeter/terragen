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
    // Swap X and Z for chunk position
    return {chunkZ, chunkX};
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
        // Generate face masks for collision detection
        int faceCount = 0;
        uint8_t chunkFaceMasks[65536 * 6] = {0}; // Maximum 6 faces per block
        
        Chunk::generateChunkFaceMasksWithNeighbors(
            currentChunk, &faceCount, 0, chunkFaceMasks,
            leftChunk, rightChunk, frontChunk, backChunk
        );
        
        // Check collisions with blocks in the current chunk
        CheckBlockCollisions(currentChunk, collider, playerPos);
        
        // Check collisions with blocks in adjacent chunks
        if (leftChunk) CheckBlockCollisions(leftChunk, collider, playerPos);
        if (rightChunk) CheckBlockCollisions(rightChunk, collider, playerPos);
        if (frontChunk) CheckBlockCollisions(frontChunk, collider, playerPos);
        if (backChunk) CheckBlockCollisions(backChunk, collider, playerPos);
    }
}

void ChunkCollisionManager::CheckBlockCollisions(Chunk* chunk, ECBS::Collider* collider, const Vector3& playerPos) {
    if (!chunk) return;
    
    // Calculate chunk world position - swap X and Z axes
    float chunkWorldZ = chunk->position.x * ChunkGovernor::CHUNK_SIZE;
    float chunkWorldX = chunk->position.y * ChunkGovernor::CHUNK_SIZE;
    
    // Check only blocks near the player (optimization)
    int minBlockX = std::max(0, static_cast<int>(floor(playerPos.x - chunkWorldX - 2)));
    int maxBlockX = std::min(ChunkGovernor::CHUNK_SIZE - 1, static_cast<int>(ceil(playerPos.x - chunkWorldX + 2)));
    int minBlockY = std::max(0, static_cast<int>(floor(playerPos.y - 2)));
    int maxBlockY = std::min(ChunkGovernor::CHUNK_HEIGHT - 1, static_cast<int>(ceil(playerPos.y + 2)));
    int minBlockZ = std::max(0, static_cast<int>(floor(playerPos.z - chunkWorldZ - 2)));
    int maxBlockZ = std::min(ChunkGovernor::CHUNK_SIZE - 1, static_cast<int>(ceil(playerPos.z - chunkWorldZ + 2)));
    
    for (int y = minBlockY; y <= maxBlockY; y++) {
        for (int z = minBlockZ; z <= maxBlockZ; z++) {
            for (int x = minBlockX; x <= maxBlockX; x++) {
                // Calculate block index
                int blockIndex = y * ChunkGovernor::CHUNK_SLICE_SIZE + z * ChunkGovernor::CHUNK_SIZE + x;
                
                // Skip air blocks (they don't collide)
                if (chunk->blocks[blockIndex].blockType == BlockType::AIR) {
                    continue;
                }
                
                // Create block bounding box in world space
                BoundingBox blockBox = {
                    {chunkWorldX + x, static_cast<float>(y), chunkWorldZ + z},
                    {chunkWorldX + x + 1, static_cast<float>(y) + 1, chunkWorldZ + z + 1}
                };
                
                // Check collision between player and block
                if (CheckCollisionBoxes(collider->boundingBox, blockBox)) {
                    // Handle collision response
                    HandleCollision(collider, blockBox);
                }
            }
        }
    }
}

void ChunkCollisionManager::HandleCollision(ECBS::Collider* collider, const BoundingBox& blockBox) {
    // Simple collision response - push player out of the block
    // This is a basic implementation that can be improved
    std::cout<<"COLISION"<<std::endl;
    // Calculate penetration depths in each axis
    float penetrationX = std::min(
        collider->boundingBox.max.x - blockBox.min.x,
        blockBox.max.x - collider->boundingBox.min.x
    );
    
    float penetrationY = std::min(
        collider->boundingBox.max.y - blockBox.min.y,
        blockBox.max.y - collider->boundingBox.min.y
    );
    
    float penetrationZ = std::min(
        collider->boundingBox.max.z - blockBox.min.z,
        blockBox.max.z - collider->boundingBox.min.z
    );
    auto parent= collider->parent->GetComponent<ECBS::RigidBody>();
    // Find minimum penetration axis (for simplest resolution)
    if (penetrationX <= penetrationY && penetrationX <= penetrationZ) {
        // X-axis resolution
        float direction = (collider->boundingBox.min.x + collider->boundingBox.max.x) / 2.0f < 
                         (blockBox.min.x + blockBox.max.x) / 2.0f ? -1.0f : 1.0f;
        /*
        collider->boundingBox.min.x += direction * penetrationX;
        collider->boundingBox.max.x += direction * penetrationX;
*/
        parent->position.x += direction * penetrationX;
    } 
    else if (penetrationY <= penetrationX && penetrationY <= penetrationZ) {
        // Y-axis resolution (usually up/down)
        float direction = (collider->boundingBox.min.y + collider->boundingBox.max.y) / 2.0f < 
                         (blockBox.min.y + blockBox.max.y) / 2.0f ? -1.0f : 1.0f;

        parent->position.y += direction * penetrationY;

        /* collider->boundingBox.min.y += direction * penetrationY;
         collider->boundingBox.max.y += direction * penetrationY;*/
    } 
    else {
        // Z-axis resolution
        float direction = (collider->boundingBox.min.z + collider->boundingBox.max.z) / 2.0f < 
                         (blockBox.min.z + blockBox.max.z) / 2.0f ? -1.0f : 1.0f;

        parent->position.z += direction * penetrationZ;

        /*collider->boundingBox.min.z += direction * penetrationZ;
        collider->boundingBox.max.z += direction * penetrationZ;*/
    }
}