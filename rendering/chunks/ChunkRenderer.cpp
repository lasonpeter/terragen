//
// Created by xenu on 08/05/2025.
//

#include <iostream>
#include "ChunkRenderer.h"
#include "../StaticRenderer.h"


void ChunkRenderer::addChunksToBeRendered(std::vector<Chunk*> *chunks, int chunkSize) {
    for (int chnk_index_x = 0; chnk_index_x < chunkSize; ++chnk_index_x) {
        for (int chnk_index_z = 0; chnk_index_z < chunkSize; ++chnk_index_z) {
            ChunkMesh *chunk_mesh = new ChunkMesh{};
            for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
                int face_count{};
                SubChunkMesh chunkMesh = SubChunkMesh();
                int *amount_of_faces = new int;
                *amount_of_faces = 0;
                Chunk::generateChunkFaceMasks(chunks->at(chnk_index_x * chunkSize + chnk_index_z), amount_of_faces, i, chunkMesh.chunkFaceMasks);
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
                            face_count = StaticRenderer::RenderCube(
                                    chunkMesh.chunkFaceMasks[y * ChunkGovernor::CHUNK_HEIGHT +
                                                             x * ChunkGovernor::CHUNK_SIZE + z], mesh.vertices,
                                    mesh.indices, mesh.texcoords, mesh.normals, new Int3{x, y, z}, face_count, chunks->at(chnk_index_x * chunkSize + chnk_index_z)->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType);
                        }
                    }
                }

                for (int z = 0; z <= mesh.vertexCount; z = z + 3) {
                    mesh.normals[z] = 0;
                    mesh.normals[z + 1] = 1;
                    mesh.normals[z + 2] = 0;
                }
                chunkMesh.mesh = mesh;
                chunk_mesh->meshes[i] = chunkMesh;
            }
            chunk_mesh->chunkPosition = chunks->at(chnk_index_x * chunkSize + chnk_index_z)->position;
            chunkMeshesCache.push_back(chunk_mesh);
        }
    }
}
void ChunkRenderer::renderChunks() {
    {
        {
            for (auto chunkModels: chunkCache->chunkModelCache) {
                    for (int i = 0; i < 16; ++i) {
                        DrawModel(chunkModels.second.subChunkModels[i],Vector3{static_cast<float>(chunkModels.second.chunkPosition.y) * ChunkGovernor::CHUNK_SIZE,static_cast<float>(i * ChunkGovernor::CHUNK_SIZE),static_cast<float>(chunkModels.second.chunkPosition.x) *ChunkGovernor::CHUNK_SIZE}, 1.0f, WHITE);
                    }
                }
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
}

void ChunkRenderer::loadTextureAtlas() {
    Image atlasImage = LoadImage("data/textures/blocks/blocks.png");
    textureAtlas = LoadTextureFromImage(atlasImage);
    textureAtlas.format = PixelFormat::PIXELFORMAT_UNCOMPRESSED_R16G16B16;
    UnloadImage(atlasImage);
}

