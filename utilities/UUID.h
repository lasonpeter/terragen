//
// Created by xenu on 12/06/2025.
//

#ifndef TERRAGEN_UUID_H
#define TERRAGEN_UUID_H

#include <cstdint>
#include <random>
#include <string>

class UUID {
public:
    // Default constructor creates a random UUID
    UUID();
    
    // Constructor from existing value
    explicit UUID(uint64_t uuid);
    
    // Get the UUID as a 64-bit integer
    uint64_t GetValue() const;
    
    // Convert to string representation
    std::string ToString() const;
    
    // Comparison operators
    bool operator==(const UUID& other) const;
    bool operator!=(const UUID& other) const;
    
    // Allow UUID to be used as key in unordered containers
    struct HashFunction {
        size_t operator()(const UUID& uuid) const;
    };

private:
    uint64_t m_UUID;
    
    // Static random number generator
    static std::mt19937_64& GetRandomEngine();
};

#endif //TERRAGEN_UUID_H
