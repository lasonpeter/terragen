//
// Created by xenu on 12/06/2025.
//

#include "ChunkCache.h"
#include "../rendering/StaticRenderer.h"
#include "../rendering/chunks/ChunkRenderer.h"

void ChunkCache::addChunk(Chunk *chunk) {
    ChunkMesh *chunk_mesh = new ChunkMesh{};
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
        int face_count{};
        SubChunkMesh chunkMesh = SubChunkMesh();
        int *amount_of_faces = new int;
        *amount_of_faces = 0;
        Chunk::generateChunkFaceMasks(chunk, amount_of_faces, i, chunkMesh.chunkFaceMasks);
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
                    face_count = StaticRenderer::RenderCube(
                            chunkMesh.chunkFaceMasks[y * ChunkGovernor::CHUNK_HEIGHT +
                                                     x * ChunkGovernor::CHUNK_SIZE + z], mesh.vertices,
                            mesh.indices, mesh.texcoords, mesh.normals, new Int3{x, y, z}, face_count, chunk->blocks[i*ChunkGovernor::SUB_CHUNK_SIZE+  y * ChunkGovernor::CHUNK_SLICE_SIZE + x * ChunkGovernor::CHUNK_SIZE +z].blockType);
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
    chunk_mesh->chunkPosition = chunk->position;
    chunkMeshesCache.insert({Int2ToString(chunk->position),chunk_mesh});

    //UPLOADS MESHES OF A CHUNK TO GPU
    for (auto& mesh: chunkMeshesCache.at(Int2ToString(chunk->position))->meshes) {
        UploadMesh(&mesh.mesh, true);
    }

    //MODEL PRE RENDERING
    ChunkModel chunkModel = ChunkModel();
    chunkModel.chunkPosition = chunkMeshesCache.at(Int2ToString(chunk->position))->chunkPosition;
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
        // THIS SHOULD NOT BE LOADED EACH TIME FROM MEMORY, LEADS TO A MEMORY LEAK
        {
            Model model =LoadModelFromMesh(chunkMeshesCache.at(Int2ToString(chunk->position))->meshes[i].mesh);
            model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = chunkRenderer->textureAtlas;
            chunkModel.subChunkModels[i] = model;
        }

    }
    chunkModelCache.insert({Int2ToString(chunk->position),chunkModel});
}
void ChunkCache::removeChunk(Int2 chunkPosition) {

}

ChunkMesh *ChunkCache::getChunkMesh(Int2 chunkPosition) {
    return nullptr;
}

ChunkModel ChunkCache::getChunkModel(Int2 chunkPosition) {
    return ChunkModel();
}

std::string ChunkCache::Int2ToString(Int2 int2) {
    return std::to_string(int2.x) + "_" + std::to_string(int2.y);
}
