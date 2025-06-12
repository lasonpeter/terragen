//
// Created by lasek on 12.06.25.
//

#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <raylib.h>


class RigidBody {
    public:
    RigidBody();
    ~RigidBody();
    BoundingBox bounding_box;
    float bounciness{};
};



#endif //RIGIDBODY_H
