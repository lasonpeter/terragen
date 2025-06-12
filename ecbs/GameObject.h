//
// Created by lasek on 12.06.25.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "../physics/PhysicsGovernor.h"

namespace ecbs {

class GameObject {
    GameObject() {
        physics::PhysicsGovernor::getInstance()->AddCallback(fixedDeltaTime);
    }
    virtual void fixedDeltaTime(float delta_t) =0;
};

} // ecbs

#endif //GAMEOBJECT_H
