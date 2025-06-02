//
// Created by xenu on 08/05/2025.
//

#include "ChunkRenderer.h"
#include "../StaticRenderer.h"


void ChunkRenderer::addChunksToBeRendered(std::vector<Chunk*> *chunks, int chunkSize) {
    for (int chnk_index_x = 0; chnk_index_x < chunkSize; ++chnk_index_x) {
        for (int chnk_index_y = 0; chnk_index_y < chunkSize; ++chnk_index_y) {
            ChunkMesh *chunk_mesh = new ChunkMesh{};
            for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
                int face_count{};
                SubChunkMesh chunkMesh = SubChunkMesh();
                int *amount_of_faces = new int;
                *amount_of_faces = 0;
                Chunk::generateChunkFaceMasks(chunks->at(chnk_index_x * chunkSize + chnk_index_y), amount_of_faces, i, chunkMesh.chunkFaceMasks,chnk_index_x, chnk_index_x, chunks,16);
                Mesh mesh = {0};
                mesh.triangleCount = (*amount_of_faces) * 2;
                mesh.vertexCount = (*amount_of_faces) * 4;
                mesh.vertices = new float[mesh.vertexCount * 3];    // 3 vertices, 3 coordinates each (x, y, z)
                mesh.texcoords = new float[mesh.vertexCount * 2];   // 3 vertices, 2 coordinates each (x, y)
                mesh.normals = new float[mesh.vertexCount * 3];     // 3 vertices, 3 coordinates each (x, y, z)
                mesh.indices = new unsigned short[mesh.triangleCount * 3];
                for (int y = 0; y < ChunkGovernor::CHUNK_SIZE; ++y) {
                    for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
                        for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                            if (is_transparent(chunks->at(chnk_index_x * chunkSize + chnk_index_y)->blocks[
                                                       y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE +
                                                       z].blockType)) {
                                continue;
                            }
                            face_count = StaticRenderer::RenderCube(
                                    chunkMesh.chunkFaceMasks[y * ChunkGovernor::CHUNK_HEIGHT +
                                                             x * ChunkGovernor::CHUNK_SIZE + z], mesh.vertices,
                                    mesh.indices, mesh.texcoords, mesh.normals, new Int3{x, y, z}, face_count);
                        }
                    }
                }

                for (int z = 0; z <= mesh.vertexCount; z = z + 3) {
                    //std::cout<<i<<std::endl;
                    mesh.normals[z] = 0;
                    mesh.normals[z + 1] = 1;
                    mesh.normals[z + 2] = 0;
                }
                chunkMesh.mesh = mesh;
                chunk_mesh->meshes[i] = chunkMesh;
            }
            chunk_mesh->chunkPosition = chunks->at(chnk_index_x * chunkSize + chnk_index_y)->position;
            chunkMeshesCache.push_back(chunk_mesh);
        }
    }
}
void ChunkRenderer::renderChunks() {
    if(modelCache.empty()) {
        for (auto chunkMesh: chunkMeshesCache) {
            for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
                // THIS SHOULD NOT BE LOADED EACH TIME FROM MEMORY, LEADS TO A MEMORY LEAK
                {
                    SubChunkModel  subChunkModel = SubChunkModel();
                    subChunkModel.model =LoadModelFromMesh(chunkMesh->meshes[i].mesh);
                    subChunkModel.position = Vector3{static_cast<float>(chunkMesh->chunkPosition.y) * ChunkGovernor::CHUNK_SIZE,static_cast<float>(i * ChunkGovernor::CHUNK_SIZE),static_cast<float>(chunkMesh->chunkPosition.x) *ChunkGovernor::CHUNK_SIZE};
                    subChunkModel.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureChecked;
                    modelCache.push_back(subChunkModel);
                    DrawModel(subChunkModel.model, Vector3{static_cast<float>(chunkMesh->chunkPosition.y) * ChunkGovernor::CHUNK_SIZE,static_cast<float>(i * ChunkGovernor::CHUNK_SIZE),static_cast<float>(chunkMesh->chunkPosition.x) *ChunkGovernor::CHUNK_SIZE}, 1.0f, WHITE);
                }
            }
        }
    }
    else{
        for (auto model: modelCache) {
            DrawModel(model.model, model.position, 1.0f, WHITE);
        }
    }
}

void ChunkRenderer::uploadMeshes() {
    for (auto chunkMesh: chunkMeshesCache) {
        for (auto & meshe : chunkMesh->meshes) {
            //ALSO TO FIX
            {
                UploadMesh(&meshe.mesh, false);
            }
        }
    }
    Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    textureChecked = LoadTextureFromImage(checked);
    UnloadImage(checked);
}

