//
// Created by xenu on 12/06/2025.
//

#include "UUID.h"
#include <sstream>
#include <iomanip>

// Initialize with a random value
UUID::UUID() 
    : m_UUID(GetRandomEngine()()) {
}

// Initialize with an existing value
UUID::UUID(uint64_t uuid) 
    : m_UUID(uuid) {
}

uint64_t UUID::GetValue() const {
    return m_UUID;
}

std::string UUID::ToString() const {
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << m_UUID;
    return ss.str();
}

bool UUID::operator==(const UUID& other) const {
    return m_UUID == other.m_UUID;
}

bool UUID::operator!=(const UUID& other) const {
    return m_UUID != other.m_UUID;
}

size_t UUID::HashFunction::operator()(const UUID& uuid) const {
    return std::hash<uint64_t>()(uuid.GetValue());
}

std::mt19937_64& UUID::GetRandomEngine() {
    // Thread-safe in C++11 and later
    static std::random_device rd;
    static std::mt19937_64 engine(rd());
    return engine;
}