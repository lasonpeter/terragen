//
// Created by xenu on 08/05/2025.
//

#include <iostream>
#include "ChunkRenderer.h"
#include "../StaticRenderer.h"
#include "../../utilities/ChunkCache.h"
#include "../../utilities/Int2ToString.h"


/*void ChunkRenderer::addChunksToBeRendered(std::vector<Chunk*> *chunks, int chunkSize) {
    for (int chnk_index_x = 0; chnk_index_x < chunkSize; ++chnk_index_x) {
        for (int chnk_index_z = 0; chnk_index_z < chunkSize; ++chnk_index_z) {
            ChunkMesh *chunk_mesh = new ChunkMesh{};
            for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
                int face_count{};
                SubChunkMesh sub_chunk_mesh = SubChunkMesh();
                int *amount_of_faces = new int;
                *amount_of_faces = 0;
                Chunk::generateChunkFaceMasks(chunks->at(chnk_index_x * chunkSize + chnk_index_z), amount_of_faces, i, sub_chunk_mesh.chunkFaceMasks);
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
                            if (is_transparent(chunks->at(chnk_index_x * chunkSize + chnk_index_z)->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType)) {
                                continue;
                            }
                            //std::cout<<"block type: " << to_string(chunks->at(chnk_index_x * chunkSize + chnk_index_y)->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE +z].blockType)<<std::endl;
                            face_count = StaticRenderer::RenderCube(
                                    sub_chunk_mesh.chunkFaceMasks[y * ChunkGovernor::CHUNK_HEIGHT +
                                                             x * ChunkGovernor::CHUNK_SIZE + z], mesh.vertices,
                                    mesh.indices, mesh.texcoords, mesh.normals, new Int3{x, y, z}, face_count, chunks->at(chnk_index_x * chunkSize + chnk_index_z)->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType);
                        }
                    }
                }

                for (int z = 0; z <= mesh.vertexCount; z = z + 3) {
                    //std::cout<<i<<std::endl;
                    mesh.normals[z] = 0;
                    mesh.normals[z + 1] = 1;
                    mesh.normals[z + 2] = 0;
                }
                sub_chunk_mesh.mesh = mesh;
                chunk_mesh->meshes[i] = sub_chunk_mesh;
            }
            chunk_mesh->chunkPosition = chunks->at(chnk_index_x * chunkSize + chnk_index_z)->position;
            chunkMeshesCache.push_back(chunk_mesh);
        }
    }
}*/

ChunkMesh * ChunkRenderer::renderMesh(Chunk* chunk){
    ChunkMesh *chunk_mesh = new ChunkMesh{};
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
        int face_count{};
        SubChunkMesh sub_chunk_mesh = SubChunkMesh();
        int *amount_of_faces = new int;
        *amount_of_faces = 0;
        Chunk::generateChunkFaceMasks(chunk, amount_of_faces, i, sub_chunk_mesh.chunkFaceMasks);
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
                    if (is_transparent(chunk->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType)) {
                        continue;
                    }
                    //std::cout<<"block type: " << to_string(chunks->at(chnk_index_x * chunkSize + chnk_index_y)->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE +z].blockType)<<std::endl;
                    face_count = StaticRenderer::RenderCube(
                            sub_chunk_mesh.chunkFaceMasks[y * ChunkGovernor::CHUNK_HEIGHT +
                                                          x * ChunkGovernor::CHUNK_SIZE + z], mesh.vertices,
                            mesh.indices, mesh.texcoords, mesh.normals, new Int3{x, y, z}, face_count, chunk->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType);
                }
            }
        }

        for (int z = 0; z <= mesh.vertexCount; z = z + 3) {
            //std::cout<<i<<std::endl;
            mesh.normals[z] = 0;
            mesh.normals[z + 1] = 1;
            mesh.normals[z + 2] = 0;
        }
        sub_chunk_mesh.mesh = mesh;
        chunk_mesh->meshes[i] = sub_chunk_mesh;
    }
    chunk_mesh->chunkPosition = chunk->position;
    return chunk_mesh;
}


/*void ChunkRenderer::renderChunks(ChunkCache* chunkCache) {
    if(chunkCache->chunk_cache_.empty()) {
        for (auto chunkMesh: chunkCache->chunk_mesh_cache_) {
            for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
                // THIS SHOULD NOT BE LOADED EACH TIME FROM MEMORY, LEADS TO A MEMORY LEAK
                {
                    SubChunkModel  subChunkModel = SubChunkModel();
                    subChunkModel.model =LoadModelFromMesh(chunkMesh.second->meshes[i].mesh);
                    subChunkModel.position = Vector3{static_cast<float>(chunkMesh.second->chunkPosition.y) * ChunkGovernor::CHUNK_SIZE,static_cast<float>(i * ChunkGovernor::CHUNK_SIZE),static_cast<float>(chunkMesh.second->chunkPosition.x) *ChunkGovernor::CHUNK_SIZE};
                    subChunkModel.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureAtlas;
                    chunkCache->chunk_mesh_cache_.insert({});
                    DrawModel(subChunkModel.model, Vector3{static_cast<float>(chunkMesh.second->chunkPosition.y) * ChunkGovernor::CHUNK_SIZE,static_cast<float>(i * ChunkGovernor::CHUNK_SIZE),static_cast<float>(chunkMesh.second->chunkPosition.x) *ChunkGovernor::CHUNK_SIZE}, 1.0f, WHITE);
                }
            }
        }
    }
    else{
        for (auto model: modelCache) {
            DrawModel(model.model, model.position, 1.0f, WHITE);
        }
    }
}*/
void ChunkRenderer::renderChunks(ChunkCache* chunkCache) {

    for (auto chunkModelsrututu : chunkCache->chunk_model_cache_) {
        SubChunkModel subChunkModel =chunkModelsrututu.second->chunk_models[0];
        DrawModel(subChunkModel.model,subChunkModel.position, 1.0f, WHITE);
    }
}

void ChunkRenderer::uploadMeshes(ChunkCache* chunkCache) {
    for (auto chunkMesh: chunkCache->chunk_mesh_cache_) {
        for (auto & meshe : chunkMesh.second->meshes) {
            //ALSO TO FIX
            {
                UploadMesh(&meshe.mesh, false);
            }
        }
    }
    Image atlasImage = LoadImage("data/textures/blocks/blocks.png");
    textureAtlas = LoadTextureFromImage(atlasImage);
    textureAtlas.format = PixelFormat::PIXELFORMAT_UNCOMPRESSED_R16G16B16;
    UnloadImage(atlasImage);
}

