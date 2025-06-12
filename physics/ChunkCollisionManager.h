//
// Created by Amazon Q on 12/06/2025.
//

#ifndef TERRAGEN_CHUNKCOLLISIONMANAGER_H
#define TERRAGEN_CHUNKCOLLISIONMANAGER_H

#include "../procedural/ChunkGovernor.h"
#include "../scripts/Player.h"
#include "../ECBS/components/RigidBody.h"
#include "../ECBS/components/Collider.h"
#include "../utilities/Mathf.h"
#include <raylib.h>

class ChunkCollisionManager {
private:
    ChunkGovernor* chunkGovernor;
    Player* player;

public:
    ChunkCollisionManager(ChunkGovernor* governor, Player* playerObj);
    ~ChunkCollisionManager() = default;

    // Get the chunk position from world position
    Int2 GetChunkPositionFromWorldPos(const Vector3& position);
    
    // Get chunk at position
    Chunk* GetChunkAtPosition(const Int2& chunkPos);
    
    // Update collisions for player's current and adjacent chunks
    void UpdateCollisions(float deltaTime);
};

#endif //TERRAGEN_CHUNKCOLLISIONMANAGER_H