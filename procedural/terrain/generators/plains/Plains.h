//
// Created by lasek on 05.04.25.
//

#ifndef PLAINS_H
#define PLAINS_H
#include "../TerrainGenerator.h"


class Plains : TerrainGenerator{
    public:
    void generateFeatures() override;

    ~Plains();
};



#endif //PLAINS_H
