//
// Created by lasek on 12.06.25.
//

#ifndef PHYSICSGOVERNOR_H
#define PHYSICSGOVERNOR_H
#include <iostream>
#include <thread>
#include <vector>
#include <bits/std_mutex.h>


#include "PhysicsGovernor.h" // Include your header file

// Required for the static local variable idiom, but no need for a separate
// static member definition for 'instance' or 'mutex_' outside the class
// because 'instance' is a local static, and 'mutex_' is no longer needed
// for the singleton pattern itself.

namespace physics {

    // Definition of the private constructor
    PhysicsGovernor::PhysicsGovernor() {
        std::cout << "PhysicsGovernor instance created." << std::endl;

        // Start the physics thread and detach it
        physicsThread_ = std::thread([this]() {
            auto last_frame_time = std::chrono::high_resolution_clock::now();
            const std::chrono::nanoseconds target_frame_duration(
                static_cast<long long>(1000000000.0 / PHYSICS_REFRESH_RATE_HZ)
            );

            while (true) {
                // In a real application, you'd want a flag to gracefully stop this loop
                // if the application is shutting down. For this example, it runs forever.

                auto current_time = std::chrono::high_resolution_clock::now();
                std::chrono::nanoseconds elapsed_time = current_time - last_frame_time;
                last_frame_time = current_time;

                float deltaTime = std::chrono::duration<float>(elapsed_time).count();

                // If AddCallback can be called concurrently with the loop,
                // you might need a lock here to protect fixedDeltaTime:
                // std::lock_guard<std::mutex> lock(internalMutex_); // If you declared internalMutex_
                for (auto functionPointer : fixedDeltaTime) {
                    if (functionPointer) { // Always good to check for nullptr if functions can be removed
                        functionPointer(deltaTime);
                    }
                }

                auto frame_end_time = std::chrono::high_resolution_clock::now();
                std::chrono::nanoseconds processing_time = frame_end_time - current_time;
                std::chrono::nanoseconds sleep_duration = target_frame_duration - processing_time;

                if (sleep_duration > std::chrono::nanoseconds::zero()) {
                    std::this_thread::sleep_for(sleep_duration);
                }
            }
        });
        physicsThread_.detach(); // Let the thread run independently
    }

    // Definition of the static getInstance method
    PhysicsGovernor* PhysicsGovernor::getInstance() {
        static PhysicsGovernor instance; // Thread-safe initialization since C++11
        return &instance;
    }

    // Definition of the AddCallback method
    void PhysicsGovernor::AddCallback(void (*fixed_delta_time)(float)) {
        // If AddCallback can be called concurrently with the physics loop,
        // you might want to protect this push_back with a mutex:
        // std::lock_guard<std::mutex> lock(internalMutex_); // If you declared internalMutex_
        fixedDeltaTime.push_back(fixed_delta_time);
    }

    // Definition of the destructor
    PhysicsGovernor::~PhysicsGovernor() {
        std::cout << "PhysicsGovernor instance destroyed." << std::endl;
        // If the thread was joinable, you might join it here or signal its exit.
        // Since it's detached and "never ends" per your description, this destructor
        // mostly serves as a notification if the process is shutting down.
    }

} // namespace physics
#endif //PHYSICSGOVERNOR_H
