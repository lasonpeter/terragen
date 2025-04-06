//
// Created by lasek on 05.04.25.
//

#include "StaticRenderer.h"

#include <raylib.h>

void StaticRenderer::render(std::vector<Chunk> *chunks) {
    Mesh mesh = { 0 };
    mesh.indices = new unsigned short[10];


    // MUST BE SET


    /*mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;*/
    mesh.vertices = new float[mesh.vertexCount*3];    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = new float[mesh.vertexCount*2];   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = new float[mesh.vertexCount*3];     // 3 vertices, 3 coordinates each (x, y, z)

    // Vertex at (0, 0, 0)

    Chunk* chunk = chunks[0].data();
    for (int y =0; y < 256; y++) {
        for (int z =0; z < 16; z++) {
            for (int x =0; x < 16; x++) {
                if (chunk->blocks[y*256+x*16+z*16].blockType == AIR  ) {
                    continue;
                }
                Block* block = &chunk->blocks[y*256+x*16+z*16];
                if (block->blockType== AIR)
                    continue;
                //CCW FACE RENDER


                //BOTTOM FACE

                // 0 [0,0,0)
                SetVertice(0, 0,0,0, mesh.vertices);
                // 1 [0,1,0]
                SetVertice(1, 1,0, 0,mesh.vertices);
                // 3 [0,1,1]
                SetVertice(2, 1,0, 1,mesh.vertices);
                // 2 [0,0,1]
                SetVertice(3, 0,0, 1,mesh.vertices);

                // BOTTOM FACE INDICIES

                //RIGHT FACE
                mesh.indices[0] = 0;
                mesh.indices[1] = 1;
                mesh.indices[2] = 3;
                //LEFT FACE
                mesh.indices[3] = 0;
                mesh.indices[4] = 3;
                mesh.indices[5] = 2;



                mesh.vertices[y*256+x*16+z+0] = x+0; //X
                mesh.vertices[1] = y+0; //Y
                mesh.vertices[2] = z+0; //Z

                mesh.normals[0] = 0; //X
                mesh.normals[1] = 1; //Y
                mesh.normals[2] = 0; //Z

                // 3 [1,0,1)
                mesh.vertices[0] = x+1; //X
                mesh.vertices[1] = y+0; //Y
                mesh.vertices[2] = z+1; //Z

                mesh.normals[0] = 0; //X
                mesh.normals[1] = 1; //Y
                mesh.normals[2] = 0; //Z

                // 1 [1,0,0)
                mesh.vertices[0] = x+1; //X
                mesh.vertices[1] = y+0; //Y
                mesh.vertices[2] = z+0; //Z

                mesh.normals[0] = 0; //X
                mesh.normals[1] = 1; //Y
                mesh.normals[2] = 0; //Z
            }
        }
    }
    mesh.vertices[0] = 0; //X
    mesh.vertices[1] = 0; //Y
    mesh.vertices[2] = 0; //Z
    mesh.normals[0] = 0; //X
    mesh.normals[1] = 1; //Y
    mesh.normals[2] = 0; //Z

    mesh.texcoords[0] = 0;
    mesh.texcoords[1] = 0;

    // Vertex at (1, 0, 2)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 0;
    mesh.vertices[5] = 2;
    mesh.normals[3] = 0;
    mesh.normals[4] = 1;
    mesh.normals[5] = 0;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0;
    mesh.normals[6] = 0;
    mesh.normals[7] = 1;
    mesh.normals[8] = 0;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] =0;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);
}

void StaticRenderer::SetVertice(int verticePositionIndex,float x, float y, float z,float* vertice) {
    vertice[verticePositionIndex+0] = x;
    vertice[verticePositionIndex+1] = y;
    vertice[verticePositionIndex+2] = z;
}


