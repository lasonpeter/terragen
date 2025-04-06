//
// Created by lasek on 05.04.25.
//

#ifndef BIOMETYPES_H
#define BIOMETYPES_H

enum BiomeType {
  PLAINS,
  FORREST,
  OCEAN,
  DESERT
};

inline const char *to_string(BiomeType e) {
  switch (e) {
    case PLAINS: return "PLAINS";
    case FORREST: return "FORREST";
    case OCEAN: return "OCEAN";
    case DESERT: return "DESERT";
    default: return "unknown";
  }
}



#endif //BIOMETYPES_H
