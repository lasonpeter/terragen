//
// Created by lasek on 05.04.25.
//
#ifndef STATICRENDERER_H
#define STATICRENDERER_H
#include <vector>

#include "../procedural/Chunk.h"

typedef struct Int3 {
    int x;
    int y;
    int z;
} Int3;

class StaticRenderer {
    public:
        void render(std::vector<Chunk>* chunks);

        static void SetVertice(int verticePositionIndex, float x, float y, float z, float *vertice);
};

#endif //STATICRENDERER_H
