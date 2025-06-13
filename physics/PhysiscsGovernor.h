//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_PHYSISCSGOVERNOR_H
#define TERRAGEN_PHYSISCSGOVERNOR_H

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>
#include <memory>

class PhysiscsGovernor {
public:
    // Define the function type for physics callbacks
    using PhysicsFunction = std::function<void(float)>;
    
    // Singleton access
    static PhysiscsGovernor* GetInstance();
    
    // Delete copy constructor and assignment operator
    PhysiscsGovernor(const PhysiscsGovernor&) = delete;
    PhysiscsGovernor& operator=(const PhysiscsGovernor&) = delete;
    
    virtual ~PhysiscsGovernor();
    
    // Start/stop the physics thread
    void Start();
    void Stop();
    
    // Add/remove physics functions using std::function
    void AddPhysicsFunction(const PhysicsFunction& func);
    void RemovePhysicsFunction(const PhysicsFunction& func) = delete; // Can't compare std::function objects
    
    // Alternative removal method using a handle
    using FunctionHandle = size_t;
    FunctionHandle AddPhysicsFunctionWithHandle(const PhysicsFunction& func);
    void RemovePhysicsFunction(FunctionHandle handle);
    
    // Called every fixed update (1/30 second)
    virtual void FixedUpdate(float delta_t);

private:
    // Private constructor for singleton
    PhysiscsGovernor();
    
    // Thread function
    void PhysicsThreadFunction();
    
    // Vector of std::function objects
    struct FunctionEntry {
        PhysicsFunction func;
        FunctionHandle handle;
    };
    std::vector<FunctionEntry> physicsFunctions;
    FunctionHandle nextHandle = 1;
    
    // Thread control
    std::thread physicsThread;
    std::atomic<bool> running;
    
    // Fixed timestep (1/30 second)
    const std::chrono::duration<float> fixedTimeStep{1.0f / 30.0f};
};

#endif //TERRAGEN_PHYSISCSGOVERNOR_H
