//
// Created by xenu on 12/06/2025.
//
#ifndef TERRAGEN_COMPONENT_H
#define TERRAGEN_COMPONENT_H


#include "uuid.h"
#include "../utilities/UUID.h"

namespace ECBS {

    class Component {
        public:
            virtual ~Component() = default;
            Component(){
                UUID uuid = UUID();
                id= uuid.GetValue();
            }
            uint64_t id;
            virtual void init() = 0;
    };

} // ECBS

#endif //TERRAGEN_COMPONENT_H
