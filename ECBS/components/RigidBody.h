//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_RIGIDBODY_H
#define TERRAGEN_RIGIDBODY_H

#include <raylib.h>
#include "../Component.h"

namespace ECBS {

    class RigidBody : public Component{
    private:
        public:
            RigidBody() = default;
            ~RigidBody() override = default;
        float mass;
        Vector3 position{};
        Vector3 velocity{};
        Vector3 acceleration{};
    };

} // ECBS

#endif //TERRAGEN_RIGIDBODY_H
