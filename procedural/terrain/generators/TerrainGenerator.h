//
// Created by lasek on 05.04.25.
//

#ifndef TERRAINGENERATOR_H
#define TERRAINGENERATOR_H

class TerrainGenerator {
public:
    virtual void generateFeatures(){};
    virtual ~TerrainGenerator()= default;
};


#endif //TERRAINGENERATOR_H
