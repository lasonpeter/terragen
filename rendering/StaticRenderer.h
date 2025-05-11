//
// Created by lasek on 05.04.25.
//
#ifndef STATICRENDERER_H
#define STATICRENDERER_H
#include <vector>

#include "../procedural/Chunk.h"


enum FaceSide{
    TOP,
    BOTTOM,
    FRONT,
    RIGHT,
    LEFT,
    BACK
};

class StaticRenderer {
    public:
        void render(std::vector<Chunk>* chunks);

        static void SetVertice(int verticePositionIndex, float x, float y, float z, float *vertice);

        static int RenderCube(uint8_t bit_mask, float *vertex_buffer, unsigned short *indicies_buffer, float *texture_buffer, float *normals_buffer, Int3 *position,int face_count);

};

#endif //STATICRENDERER_H
