//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_GAMEOBJECTGOVERNOR_H
#define TERRAGEN_GAMEOBJECTGOVERNOR_H

#include <unordered_map>
#include "GameObject.h"

namespace ECBS {

    class GameObjectGovernor {
        public:
            GameObjectGovernor() = default;
            ~GameObjectGovernor() = default;
            std::unordered_map<uint64_t, GameObject*> gameObjects{};

            void addGameObject(GameObject* gameObject) {
                gameObjects[gameObject->GetId()] = gameObject;
            }

            void removeGameObject(GameObject* gameObject) {
                if(gameObjects.contains(gameObject->GetId())) {
                    gameObjects.erase(gameObject->GetId());
                    return;
                }
                throw std::invalid_argument("GameObject not found");
            }


            void removeGameObject(uint64_t id) {
                if(gameObjects.contains(id)) {
                    gameObjects.erase(id);
                    return;
                }
                throw std::invalid_argument("GameObject not found");

            }
    };

} // ECBS

#endif //TERRAGEN_GAMEOBJECTGOVERNOR_H
