//
// Created by xenu on 12/06/2025.
//

#include <iostream>
#include "Player.h"

void Player::fixedDeltaTime(float delta_t) {
    std::cout<<"delta_t: "<<delta_t<<"ID:" << GetId()<<std::endl;
}
