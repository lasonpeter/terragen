//
// Created by xenu on 08/05/2025.
//

#include "ChunkRenderer.h"
#include "../StaticRenderer.h"


void ChunkRenderer::addChunksToBeRendered(std::vector<Chunk*> *chunks) {
    for (auto chunk : *chunks) {
        int face_count{};
        ChunkMesh *chunkMesh = new ChunkMesh();
        int *amount_of_faces = new int;
        *amount_of_faces = 0;
        uint8_t* chunkFaceMasks = Chunk::generateChunkFaceMasks(chunk,amount_of_faces);
        Mesh mesh = { 0 };
        mesh.triangleCount = (*amount_of_faces)*2;
        mesh.vertexCount = (*amount_of_faces)*4;
        mesh.vertices = new float[mesh.vertexCount*3];    // 3 vertices, 3 coordinates each (x, y, z)
        mesh.texcoords = new float[mesh.vertexCount*2];   // 3 vertices, 2 coordinates each (x, y)
        mesh.normals = new float[mesh.vertexCount*3];     // 3 vertices, 3 coordinates each (x, y, z)
        mesh.indices = new unsigned short[mesh.triangleCount*3];
        for (int y = 0; y < 256; ++y) {
            for (int x = 0; x < 16; ++x) {
                for (int z = 0; z < 16; ++z) {
                    if(is_transparent(chunk->blocks[y*256+x*16+z].blockType)){
                        continue;
                    }
                    face_count =StaticRenderer::RenderCube(chunkFaceMasks[y*256+x*16+z], mesh.vertices,mesh.indices,mesh.texcoords,mesh.normals,new Int3{x,y,z},face_count);
                }
            }
        }

        for (int i = 0; i <= mesh.vertexCount; i=i+3) {
            //std::cout<<i<<std::endl;
            mesh.normals[i] = 0;
            mesh.normals[i+1] = 1;
            mesh.normals[i+2] = 0;
        }
        std::copy(chunkFaceMasks, chunkFaceMasks + ChunkGovernor::CHUNK_HEIGHT*ChunkGovernor::CHUNK_SIZE*ChunkGovernor::CHUNK_SIZE, chunkMesh->chunkFaceMasks);
        chunkMesh->chunkPosition = chunk->position;
        chunkMesh->mesh = mesh;
        chunkMeshesCache.push_back(chunkMesh);
    }

}

void ChunkRenderer::renderChunks() {
    for (auto chunkMesh:chunkMeshesCache) {
        Model model= LoadModelFromMesh(chunkMesh->mesh);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureChecked;
        DrawModel(model, Vector3{static_cast<float>(chunkMesh->chunkPosition.y)*ChunkGovernor::CHUNK_SIZE, 0, static_cast<float>(chunkMesh->chunkPosition.x)*ChunkGovernor::CHUNK_SIZE}, 1.0f, WHITE);
    }
}

void ChunkRenderer::uploadMeshes() {
    for (auto chunkMesh: chunkMeshesCache) {
        UploadMesh(&chunkMesh->mesh, false);
    }
    Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    textureChecked = LoadTextureFromImage(checked);
    UnloadImage(checked);


}

