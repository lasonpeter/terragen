//
// Created by xenu on 06/05/2025.
//

#ifndef TERRAGEN_FACEMASK_H
#define TERRAGEN_FACEMASK_H

#include <cstdint>

enum class FaceMask : uint8_t {
    None    = 0,          // 0000 0000
    Top     = 1 << 0,       // 0000 0001
    Bottom  = 1 << 1,   // 0000 0010
    Front   = 1 << 2,    // 0000 0100
    Right   = 1 << 3,     // 0000 1000
    Back    = 1 << 4,      // 0001 0000
    Left    = 1 << 5        // 0010 0000
};
inline FaceMask operator|(FaceMask a, FaceMask b) {
    return static_cast<FaceMask>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline FaceMask operator&(FaceMask a, FaceMask b) {
    return static_cast<FaceMask>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline FaceMask operator~(FaceMask a) {
    return static_cast<FaceMask>(~static_cast<uint8_t>(a));
}

inline uint8_t operator+(uint8_t bitmask, FaceMask face) {
    // Performs bitwise OR to set the flag
    return bitmask | static_cast<uint8_t>(face);
}

inline uint8_t operator-(uint8_t bitmask, FaceMask face) {
    // Performs bitwise AND with the complement to clear the flag
    return bitmask & ~static_cast<uint8_t>(face);
}
#endif //TERRAGEN_FACEMASK_H
