//
// Created by xenu on 12/06/2025.
//

#include <iostream>
#include "Player.h"
#include "../ECBS/components/RigidBody.h"
#include "../ECBS/components/Collider.h"

void Player::fixedDeltaTime(float delta_t) {
    std::cout<<"delta_t: "<<delta_t<<"ID:" << GetId()<<std::endl;
    
    // Update player position for collision detection
    auto* rigidBody = GetComponent<ECBS::RigidBody>();
    auto* collider = GetComponent<ECBS::Collider>();
    
    if (rigidBody && collider) {
        // Update collider position based on camera position
        // This would be replaced with actual player position logic
        // For now, we're just updating the bounding box for demonstration
        Vector3 position = {camera.position.x, camera.position.y, camera.position.z};
        collider->boundingBox.min = Vector3{position.x - 0.5f, position.y - 1.0f, position.z - 0.5f};
        collider->boundingBox.max = Vector3{position.x + 0.5f, position.y + 1.0f, position.z + 0.5f};
    }
}
