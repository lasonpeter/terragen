//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_PLAYER_H
#define TERRAGEN_PLAYER_H

#include "../ECBS/GameObject.h"

class Player : ECBS::GameObject {
    void fixedDeltaTime(float delta_t) override;
};


#endif //TERRAGEN_PLAYER_H
