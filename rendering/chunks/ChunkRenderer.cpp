//
// Created by xenu on 08/05/2025.
//

#include <iostream>
#include "ChunkRenderer.h"
#include "../StaticRenderer.h"
#include "../../utilities/ChunkCache.h"
#include "../../utilities/Int2ToString.h"
#include "../../procedural/ChunkGovernor.h"


ChunkMesh * ChunkRenderer::renderMesh(Chunk* chunk){
    ChunkMesh *chunk_mesh = new ChunkMesh{};
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
        int face_count{};
        SubChunkMesh* sub_chunk_mesh = new SubChunkMesh();
        int *amount_of_faces = new int;
        *amount_of_faces = 0;
        Chunk::generateChunkFaceMasks(chunk, amount_of_faces, i, sub_chunk_mesh->chunkFaceMasks);
        Mesh* mesh = new Mesh{0};
        mesh->triangleCount = (*amount_of_faces) * 2;
        mesh->vertexCount = (*amount_of_faces) * 4;
        mesh->vertices = new float[mesh->vertexCount * 3];    // 3 vertices, 3 coordinates each (x, y, z)
        mesh->texcoords = new float[mesh->vertexCount * 2];   // 3 vertices, 2 coordinates each (x, y)
        mesh->normals = new float[mesh->vertexCount * 3];     // 3 vertices, 3 coordinates each (x, y, z)
        mesh->indices = new unsigned short[mesh->triangleCount * 3];
        for (int y = 0; y < ChunkGovernor::CHUNK_SIZE; ++y) {
            for (int x = 0; x < ChunkGovernor::CHUNK_SIZE; ++x) {
                for (int z = 0; z < ChunkGovernor::CHUNK_SIZE; ++z) {
                    if (is_transparent(chunk->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType)) {
                        continue;
                    }
                    //std::cout<<"block type: " << to_string(chunks->at(chnk_index_x * chunkSize + chnk_index_y)->blocks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE +z].blockType)<<std::endl;
                    face_count = StaticRenderer::RenderCube(sub_chunk_mesh->chunkFaceMasks[y * ChunkGovernor::CHUNK_HEIGHT + x * ChunkGovernor::CHUNK_SIZE + z], mesh->vertices,mesh->indices, mesh->texcoords, mesh->normals, new Int3{x, y, z}, face_count, chunk->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType);
                }
            }
        }

        for (int z = 0; z <= mesh->vertexCount; z = z + 3) {
            //std::cout<<i<<std::endl;
            mesh->normals[z] = 0;
            mesh->normals[z + 1] = 1;
            mesh->normals[z + 2] = 0;
        }
        sub_chunk_mesh->mesh = mesh;
        chunk_mesh->meshes[i] = sub_chunk_mesh;
    }
    chunk_mesh->chunkPosition = chunk->position;
    return chunk_mesh;
}

void ChunkRenderer::renderChunks(ChunkCache* chunkCache) {

    for (auto chunkModelsrututu : chunkCache->chunk_model_cache_) {
        for (auto subChunkModel : chunkModelsrututu.second->chunk_models) {
            //std::cout<<"YOur matkas position: " << subChunkModel.position.x << " " << subChunkModel.position.y << " " << subChunkModel.position.z << std::endl;

            DrawModel(subChunkModel->model, subChunkModel->position, 1.0f, WHITE);
        }
    }
}

void ChunkRenderer::uploadMeshes(ChunkCache* chunkCache) {
    for (auto chunkMesh: chunkCache->chunk_mesh_cache_) {
        for (auto mesh : chunkMesh.second->meshes) {
            {
                std::cout<<&mesh->mesh<<std::endl;
                UploadMesh(mesh->mesh, false);
            }
        }
    }
}

void ChunkRenderer::uploadTextureAtlas() {
    Image atlasImage = LoadImage("data/textures/blocks/blocks.png");
    textureAtlas = LoadTextureFromImage(atlasImage);
    textureAtlas.format = PixelFormat::PIXELFORMAT_UNCOMPRESSED_R16G16B16;
    UnloadImage(atlasImage);
}
