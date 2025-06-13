//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_PLAYER_H
#define TERRAGEN_PLAYER_H

#include "../ECBS/GameObject.h"
#include <raylib.h>

class Player : public ECBS::GameObject {
public:
    Camera3D camera{}; // Reference to the camera for position updates
    std::string username{};
    void fixedDeltaTime(float delta_t) override;
};


#endif //TERRAGEN_PLAYER_H
