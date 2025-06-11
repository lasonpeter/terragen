//
// Created by lasek on 11.06.25.
//

#include "ChunkCache.h"
#include "../utilities/Int2ToString.h"
#include "../rendering/chunks/ChunkRenderer.h"
#include "../procedural/ChunkGovernor.h"

void ChunkCache::addChunk(Chunk *chunk,ChunkRenderer* chunkRenderer) {
    ChunkMesh* pChunkMesh= ChunkRenderer::renderMesh(chunk);
    chunk_mesh_cache_.insert(std::make_pair(Int2ToString::to_string(chunk->position),pChunkMesh));
    auto* chunkModel = new ChunkModel();
    for (int i = 0; i < ChunkGovernor::CHUNK_SIZE; ++i) {
        // THIS SHOULD NOT BE LOADED EACH TIME FROM MEMORY, LEADS TO A MEMORY LEAK
        {
            SubChunkModel  subChunkModel = SubChunkModel();
            subChunkModel.model =LoadModelFromMesh(pChunkMesh->meshes[i].mesh);
            subChunkModel.position = Vector3{static_cast<float>(pChunkMesh->chunkPosition.y) * ChunkGovernor::CHUNK_SIZE,static_cast<float>(i * ChunkGovernor::CHUNK_SIZE),static_cast<float>(pChunkMesh->chunkPosition.x) *ChunkGovernor::CHUNK_SIZE};
            subChunkModel.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = chunkRenderer->textureAtlas;

            chunkModel->chunk_models[i] = subChunkModel;
            /*DrawModel(subChunkModel.model, Vector3{static_cast<float>(chunkMesh.second->chunkPosition.y) * ChunkGovernor::CHUNK_SIZE,static_cast<float>(i * ChunkGovernor::CHUNK_SIZE),static_cast<float>(chunkMesh.second->chunkPosition.x) *ChunkGovernor::CHUNK_SIZE}, 1.0f, WHITE);*/
        }
    }
    chunk_model_cache_.insert(std::make_pair(Int2ToString::to_string(chunk->position), chunkModel));
}

void ChunkCache::removeChunk(Int2 chunkId) {
    delete chunk_mesh_cache_.at(Int2ToString::to_string(chunkId));
    chunk_mesh_cache_.erase(Int2ToString::to_string(chunkId));
    delete chunk_mesh_cache_.at(Int2ToString::to_string(chunkId));
    chunk_cache_.erase(Int2ToString::to_string(chunkId));
    for (const auto& chunkModel: chunk_model_cache_) {
        for (auto & chunk_model : chunkModel.second->chunk_models) {
            UnloadModel(chunk_model.model);
        }
        delete chunkModel.second;
    }
    delete chunk_model_cache_.at(Int2ToString::to_string(chunkId));
    chunk_model_cache_.erase(Int2ToString::to_string(chunkId));
}