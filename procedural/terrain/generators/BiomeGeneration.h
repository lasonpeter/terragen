//
// Created by PC on 12.06.2025.
//

#ifndef BIOMEGENERATION_H
#define BIOMEGENERATION_H
#include <cstdint>
#include <raylib.h>


class BiomeGeneration {
public:
    Vector2 forest{0.5, 0.8};
    Vector2 mountains{0.3, 0.4};
    Vector2 desert{0.9, 0.1};
};

namespace world {
    enum class Biome : uint8_t {
        Forest,
        Mountains,
        Desert,
      };
}


#endif //BIOMEGENERATION_H
