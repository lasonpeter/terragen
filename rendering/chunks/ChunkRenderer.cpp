//
// Created by xenu on 08/05/2025.
//

#include <iostream>
#include "ChunkRenderer.h"
#include "../StaticRenderer.h"


void ChunkRenderer::addChunksToBeRendered(std::vector<Chunk*> *chunks) {
    for (auto chunk : *chunks) {
        ChunkMesh *chunkMesh = new ChunkMesh();
        for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i){
            int face_count{};
            int *amount_of_faces = new int;
            *amount_of_faces = 0;
            uint8_t* chunkFaceMasks = Chunk::generateChunkFaceMasks(chunk,amount_of_faces,i);
            Mesh mesh = { 0 };
            mesh.triangleCount = (*amount_of_faces)*2;
            mesh.vertexCount = (*amount_of_faces)*4;
            mesh.vertices = new float[mesh.vertexCount*3];    // 3 vertices, 3 coordinates each (x, y, z)
            mesh.texcoords = new float[mesh.vertexCount*2];   // 3 vertices, 2 coordinates each (x, y)
            mesh.normals = new float[mesh.vertexCount*3];     // 3 vertices, 3 coordinates each (x, y, z)
            mesh.indices = new unsigned short[mesh.triangleCount*3];

            ///TO FINISH
            for (int y = 0; y < ChunkGovernor::CHUNK_SIZE; ++y) {
                for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
                    for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                        if (is_transparent(chunk->blocks[i*ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE+ y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType)) {
                            continue;
                        }
                        face_count = StaticRenderer::RenderCube(
                                chunkFaceMasks[y * ChunkGovernor::CHUNK_SIZE + x * ChunkGovernor::CHUNK_SIZE + z],
                                mesh.vertices, mesh.indices, mesh.texcoords, mesh.normals, new Int3{x, y, z},
                                face_count);
                    }
                }
            }
            std::cout << "Face Count: " << face_count * 4 << std::endl;
            std::cout << "Verticies Count: " << face_count * 4 << std::endl;

            for (int c = 0; c <= mesh.vertexCount; c = c + 3) {
                //std::cout<<i<<std::endl;
                mesh.normals[c] = 0;
                mesh.normals[c + 1] = 1;
                mesh.normals[c + 2] = 0;
            }
            std::cout<<"OHO"<<std::endl;
            std::copy(
                    chunkFaceMasks, //copy from, start iterator
                    chunkFaceMasks +ChunkGovernor::CHUNK_SIZE * ChunkGovernor::CHUNK_SIZE * ChunkGovernor::CHUNK_SIZE, //copy from, ending iterator
                    chunkMesh->chunkFaceMasks+ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE*i); //copy to starting iterator, this one changes as to offset next generated facemasks into respective positions

                    chunkMesh->chunkMeshes.push_back(mesh);
        }
        chunkMesh->chunkPosition = chunk->position;
        chunkMeshesCache.push_back(chunkMesh);
    }
}

void ChunkRenderer::renderChunks() {
    for (auto chunkMesh:chunkMeshesCache) {
        for (auto mesh:chunkMesh->chunkMeshes) {
            int y=0;
            Model model= LoadModelFromMesh(mesh);
            model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureChecked;
            DrawModel(model, Vector3{static_cast<float>(chunkMesh->chunkPosition.y)*ChunkGovernor::CHUNK_SIZE,static_cast<float>(y*ChunkGovernor::CHUNK_SIZE) , static_cast<float>(chunkMesh->chunkPosition.x)*ChunkGovernor::CHUNK_SIZE}, 1.0f, WHITE);
            y++;
        }
    }
}

void ChunkRenderer::uploadMeshes() {
    for (auto chunkMesh: chunkMeshesCache) {
        for (auto meshOfChunk:chunkMesh->chunkMeshes) {
            UploadMesh(&meshOfChunk, false);
        }
    }
    Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    textureChecked = LoadTextureFromImage(checked);
    UnloadImage(checked);


}

