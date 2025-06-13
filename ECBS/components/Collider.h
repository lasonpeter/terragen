//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_COLLIDER_H
#define TERRAGEN_COLLIDER_H

#include <raylib.h>
#include "../Component.h"

namespace ECBS {

    class Collider: public Component{
        public:
            Collider() = default;
            BoundingBox boundingBox{};
    };

} // ECBS

#endif //TERRAGEN_COLLIDER_H
