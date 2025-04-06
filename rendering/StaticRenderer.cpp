//
// Created by lasek on 05.04.25.
//

#include "StaticRenderer.h"

#include <raylib.h>

void StaticRenderer::render(std::vector<Chunk> *chunks) {
    Mesh mesh = { 0 };
   // mesh.indices = new unsigned short[10];


    // MUST BE SET


    /*mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;*/
    mesh.vertices = new float[mesh.vertexCount*3];    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = new float[mesh.vertexCount*2];   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = new float[mesh.vertexCount*3];     // 3 vertices, 3 coordinates each (x, y, z)

    // Vertex at (0, 0, 0)

    Chunk* chunk = chunks[0].data();
    int indiciesCounter = 0;
    int textureCounter = 0;
    int vertexCounter = 0;
    for (int y =0; y < 256; y++) {
        for (int z =0; z < 16; z++) {
            for (int x =0; x < 16; x++) {
                if (chunk->blocks[y*256+x*16+z*16].blockType == AIR  ) {
                    continue;
                }
                Block* block = &chunk->blocks[y*256+z*16+x];
                if (block->blockType== AIR)
                    continue;
                //CCW FACE RENDER
                {
                    if(x<15)
                    {
                        if (chunk->blocks[y*256+z*16+x+1].isTransparent)
                        {
                            //RENDER RIGHT FACE


                        }
                    }
                    if (x>0)
                    {
                        if (chunk->blocks[y*256+z*16+x-1].isTransparent)
                        {
                            //RENDER LEFT FACE
                        }
                    }
                    if(z<15)
                    {
                        if (chunk->blocks[y*256+(z+1)*16+x].isTransparent)
                        {
                            //RENDER FRONT FACE
                        }
                    }
                    if (z>0)
                    {
                        if (chunk->blocks[y*256+(z-1)*16+x].isTransparent)
                        {
                            //RENDER BACK FACE
                        }
                    }
                    if(y<15)
                    {
                        if (chunk->blocks[(y+1)*256+z*16+x].isTransparent)
                        {
                            //RENDER TOP FACE
                        }
                    }
                    if (y>0)
                    {
                        if (chunk->blocks[(y-1)*256+z*16+x].isTransparent)
                        {
                            //RENDER BOTTOM FACE
                        }
                    }
                }

                //TOP FACE
                SetVertice(vertexCounter++, 0,1, 0,mesh.vertices);
                SetVertice(vertexCounter++, 1,1,0, mesh.vertices);
                SetVertice(vertexCounter++, 0,1, 1,mesh.vertices);
                SetVertice(vertexCounter++, 1,1, 1,mesh.vertices);

                //RIGHT TRIANGLE
                mesh.indices[0] = 3;
                mesh.indices[1] = 1;
                mesh.indices[2] = 0;

                //LEFT TRIANGLE
                mesh.indices[3] = 2;
                mesh.indices[4] = 3;
                mesh.indices[5] = 0;

                //TEXTURES
                mesh.texcoords[textureCounter++] = 1; //X
                mesh.texcoords[textureCounter++] = 0; //Y

                mesh.texcoords[textureCounter++] = 0; //X
                mesh.texcoords[textureCounter++] = 0; //Y

                mesh.texcoords[textureCounter++] = 1; //X
                mesh.texcoords[textureCounter++] = 1; //Y

                mesh.texcoords[textureCounter++] = 0; //X
                mesh.texcoords[textureCounter++] = 1; //Y

            }
        }
    }

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);
}

void StaticRenderer::SetVertice(int verticePositionIndex,float x, float y, float z,float* vertice) {
    vertice[verticePositionIndex*3+0] = x;
    vertice[verticePositionIndex*3+1] = y;
    vertice[verticePositionIndex*3+2] = z;
}


