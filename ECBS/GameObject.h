//
// Created by lasek on 12.06.25.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../physics/PhysiscsGovernor.h"
#include "Component.h"
#include <functional>
#include <typeindex>

namespace ECBS {

    class GameObject {

    private:
        const uint64_t id =UUID().GetValue();;

    public:
        GameObject() {
            // Use std::bind to bind the member function to this instance
            auto boundFunction = std::bind(&GameObject::fixedDeltaTime, this, std::placeholders::_1);
            // Store the handle so we can remove it later
            physicsHandle = PhysiscsGovernor::GetInstance()->AddPhysicsFunctionWithHandle(boundFunction);
        }

        virtual ~GameObject() {
            // Remove the physics function when the object is destroyed
            if (physicsHandle != 0) {
                PhysiscsGovernor::GetInstance()->RemovePhysicsFunction(physicsHandle);
            }
        }
        template<typename T>
        T* AddComponent() {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
            T* component = new T();
            //God left this world after this
            Component *comp= ((Component*) component );
            comp->parent=this;
            components[std::type_index(typeid(T))].push_back(component);
            return component;
    }

        template<typename T>
        T* GetComponent() {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
            auto it = components.find(std::type_index(typeid(T)));
            if (it != components.end() && !it->second.empty()) {
                return static_cast<T*>(it->second[0]); // Return first component of this type
            }
            return nullptr;
        }

        template<typename T>
        std::vector<T*> GetComponents() {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
            std::vector<T*> result;
            auto it = components.find(std::type_index(typeid(T)));
            if (it != components.end()) {
                for (auto* comp : it->second) {
                    result.push_back(static_cast<T*>(comp));
                }
            }
            return result;
        }

        uint64_t GetId() const {
            return id;
        }

        virtual void fixedDeltaTime(float delta_t) = 0;
    private:
        std::unordered_map<std::type_index, std::vector<Component*>> components{};
        // Store the handle for later removal
        PhysiscsGovernor::FunctionHandle physicsHandle = 0;
    };

} // ECBS

#endif //GAMEOBJECT_H
