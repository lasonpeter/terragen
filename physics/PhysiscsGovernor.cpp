//
// Created by xenu on 12/06/2025.
//

#include "PhysiscsGovernor.h"
#include <algorithm>
#include <thread>
#include <iostream>
#include <raylib.h>

// Static instance getter implementation
PhysiscsGovernor* PhysiscsGovernor::GetInstance() {
    static PhysiscsGovernor instance;
    return &instance;
}

PhysiscsGovernor::PhysiscsGovernor() : running(false), nextHandle(1) {
}

PhysiscsGovernor::~PhysiscsGovernor() {
    Stop();
}

void PhysiscsGovernor::Start() {
    if (!running.exchange(true)) {
        physicsThread = std::thread(&PhysiscsGovernor::PhysicsThreadFunction, this);
    }
}

void PhysiscsGovernor::Stop() {
    if (running.exchange(false)) {
        if (physicsThread.joinable()) {
            physicsThread.join();
        }
    }
}

void PhysiscsGovernor::AddPhysicsFunction(const PhysicsFunction& func) {
    if (func) {
        FunctionEntry entry{func, nextHandle++};
        physicsFunctions.push_back(entry);
    }
}

PhysiscsGovernor::FunctionHandle PhysiscsGovernor::AddPhysicsFunctionWithHandle(const PhysicsFunction& func) {
    if (func) {
        FunctionHandle handle = nextHandle++;
        FunctionEntry entry{func, handle};
        physicsFunctions.push_back(entry);
        return handle;
    }
    return 0; // Invalid handle
}

void PhysiscsGovernor::RemovePhysicsFunction(FunctionHandle handle) {
    auto it = std::find_if(physicsFunctions.begin(), physicsFunctions.end(),
                          [handle](const FunctionEntry& entry) {
                              return entry.handle == handle;
                          });
    if (it != physicsFunctions.end()) {
        physicsFunctions.erase(it);
    }
}

void PhysiscsGovernor::FixedUpdate(float delta_t) {
    // Execute all registered physics functions
    for (const auto& entry : physicsFunctions) {
        if (entry.func) {
            entry.func(delta_t);
        }
    }
}

void PhysiscsGovernor::PhysicsThreadFunction() {
    using clock = std::chrono::high_resolution_clock;
    
    auto previousTime = clock::now();
    std::chrono::duration<float> accumulator(0.0f);
    
    while (running) {
        auto currentTime = clock::now();
        auto frameTime = currentTime - previousTime;
        previousTime = currentTime;
        
        // Cap frame time to avoid spiral of death
        
        accumulator += frameTime;
        
        // Fixed timestep update
        while (accumulator >= fixedTimeStep) {
            //std::cout<<"FixedUpdate"<<std::endl;
            FixedUpdate(1.0f/30.0f);
            accumulator -= fixedTimeStep;
        }
        
        // Sleep to avoid consuming too much CPU
        if (accumulator < fixedTimeStep) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1/30));
        }
    }
}
