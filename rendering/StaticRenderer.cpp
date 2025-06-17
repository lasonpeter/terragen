//
// Created by lasek on 05.04.25.
//

#include "StaticRenderer.h"

#include <raylib.h>
#include <iostream>

void StaticRenderer::SetVertice(int verticePositionIndex,float x, float y, float z,float* vertice) {
    vertice[verticePositionIndex*3+0] = x;
    vertice[verticePositionIndex*3+1] = y;
    vertice[verticePositionIndex*3+2] = z;
}

/// Function for rendering cube's faces
/// \param bit_mask bit mask indicating which faces to render
/// \param vertex_buffer self explanatory
/// \param indicies_buffer self explanatory
/// \param texture_buffer self explanatory
/// \param normals_buffer self explanatory
/// \param position self explanatoryE
/// \return number of faces rendered
int StaticRenderer::RenderCube(uint8_t bit_mask, float *vertex_buffer, unsigned short *indicies_buffer, float *texture_buffer, float *normals_buffer, Int3 *position, int face_count, BlockType blockType) {

    // Helper lambda for assigning texture coordinates (reused for all faces)
    auto assignTextureCoords = [&](int faceIndex) {
        //std::cout << uv_coords(blockType).positionX/StaticRenderer::ATLAS_SIZE + uv_coords(blockType).sourceWidth/StaticRenderer::ATLAS_SIZE << std::endl;
        texture_buffer[0 + (8 * faceIndex)] = ( uv_coords(blockType).positionX/StaticRenderer::ATLAS_SIZE + uv_coords(blockType).sourceWidth/StaticRenderer::ATLAS_SIZE); // X
        texture_buffer[1 + (8 * faceIndex)] = (uv_coords(blockType).positionY/StaticRenderer::ATLAS_SIZE); // Y

        texture_buffer[2 + (8 * faceIndex)] = uv_coords(blockType).positionX/StaticRenderer::ATLAS_SIZE; // X
        texture_buffer[3 + (8 * faceIndex)] = (uv_coords(blockType).positionY/StaticRenderer::ATLAS_SIZE); // Y

        texture_buffer[4 + (8 * faceIndex)] = uv_coords(blockType).positionX/StaticRenderer::ATLAS_SIZE + uv_coords(blockType).sourceWidth/StaticRenderer::ATLAS_SIZE; // X
        texture_buffer[5 + (8 * faceIndex)] = (uv_coords(blockType).positionY/StaticRenderer::ATLAS_SIZE + uv_coords(blockType).sourceHeight/StaticRenderer::ATLAS_SIZE); // Y

        texture_buffer[6 + (8 * faceIndex)] = ( uv_coords(blockType).positionX/StaticRenderer::ATLAS_SIZE); // X
        texture_buffer[7 + (8 * faceIndex)] = (uv_coords(blockType).positionY/StaticRenderer::ATLAS_SIZE + uv_coords(blockType).sourceHeight/StaticRenderer::ATLAS_SIZE); // Y
    };

    // Top Face
    if (bit_mask & (1 << 0)) {  // Top face bit
        StaticRenderer::SetVertice(0 + (4 * face_count), 0 + position->x, 1 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(1 + (4 * face_count), 1 + position->x, 1 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(2 + (4 * face_count), 0 + position->x, 1 + position->y, 1 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(3 + (4 * face_count), 1 + position->x, 1 + position->y, 1 + position->z, vertex_buffer);

        indicies_buffer[0 + (6 * face_count)] = 3 + (4 * face_count);
        indicies_buffer[1 + (6 * face_count)] = 1 + (4 * face_count);
        indicies_buffer[2 + (6 * face_count)] = 0 + (4 * face_count);

        indicies_buffer[3 + (6 * face_count)] = 2 + (4 * face_count);
        indicies_buffer[4 + (6 * face_count)] = 3 + (4 * face_count);
        indicies_buffer[5 + (6 * face_count)] = 0 + (4 * face_count);

        assignTextureCoords(face_count);
        face_count++;
    }

    // Bottom Face
    if (bit_mask & (1 << 1)) {  // Bottom face bit
        StaticRenderer::SetVertice(0 + (4 * face_count), 0 + position->x, 0 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(1 + (4 * face_count), 1 + position->x, 0 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(2 + (4 * face_count), 0 + position->x, 0 + position->y, 1 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(3 + (4 * face_count), 1 + position->x, 0 + position->y, 1 + position->z, vertex_buffer);

        indicies_buffer[0 + (6 * face_count)] = 0 + (4 * face_count);
        indicies_buffer[1 + (6 * face_count)] = 1 + (4 * face_count);
        indicies_buffer[2 + (6 * face_count)] = 3 + (4 * face_count);

        indicies_buffer[3 + (6 * face_count)] = 0 + (4 * face_count);
        indicies_buffer[4 + (6 * face_count)] = 3 + (4 * face_count);
        indicies_buffer[5 + (6 * face_count)] = 2 + (4 * face_count);

        assignTextureCoords(face_count);
        face_count++;
    }

    // Front Face
    if (bit_mask & (1 << 2)) {  // Front face bit
        StaticRenderer::SetVertice(0 + (4 * face_count), 0 + position->x, 0 + position->y, 1 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(1 + (4 * face_count), 1 + position->x, 0 + position->y, 1 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(2 + (4 * face_count), 0 + position->x, 1 + position->y, 1 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(3 + (4 * face_count), 1 + position->x, 1 + position->y, 1 + position->z, vertex_buffer);

        indicies_buffer[0 + (6 * face_count)] = 0 + (4 * face_count);
        indicies_buffer[1 + (6 * face_count)] = 1 + (4 * face_count);
        indicies_buffer[2 + (6 * face_count)] = 3 + (4 * face_count);

        indicies_buffer[3 + (6 * face_count)] = 0 + (4 * face_count);
        indicies_buffer[4 + (6 * face_count)] = 3 + (4 * face_count);
        indicies_buffer[5 + (6 * face_count)] = 2 + (4 * face_count);

        assignTextureCoords(face_count);
        face_count++;
    }

    // Back Face
    if (bit_mask & (1 << 4)) {  // Back face bit
        StaticRenderer::SetVertice(0 + (4 * face_count), 0 + position->x, 0 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(1 + (4 * face_count), 1 + position->x, 0 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(2 + (4 * face_count), 0 + position->x, 1 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(3 + (4 * face_count), 1 + position->x, 1 + position->y, 0 + position->z, vertex_buffer);

        indicies_buffer[0 + (6 * face_count)] = 1 + (4 * face_count);
        indicies_buffer[1 + (6 * face_count)] = 0 + (4 * face_count);
        indicies_buffer[2 + (6 * face_count)] = 2 + (4 * face_count);

        indicies_buffer[3 + (6 * face_count)] = 1 + (4 * face_count);
        indicies_buffer[4 + (6 * face_count)] = 2 + (4 * face_count);
        indicies_buffer[5 + (6 * face_count)] = 3 + (4 * face_count);

        assignTextureCoords(face_count);
        face_count++;
    }

    // Right Face
    if (bit_mask & (1 << 3)) {  // Right face bit
        StaticRenderer::SetVertice(0 + (4 * face_count), 1 + position->x, 0 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(1 + (4 * face_count), 1 + position->x, 0 + position->y, 1 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(2 + (4 * face_count), 1 + position->x, 1 + position->y, 0 + position->z, vertex_buffer);
        StaticRenderer::SetVertice(3 + (4 * face_count), 1 + position->x, 1 + position->y, 1 + position->z, vertex_buffer);

        indicies_buffer[0 + (6 * face_count)] = 1 + (4 * face_count);
        indicies_buffer[1 + (6 * face_count)] = 0 + (4 * face_count);
        indicies_buffer[2 + (6 * face_count)] = 2 + (4 * face_count);

        indicies_buffer[3 + (6 * face_count)] = 1 + (4 * face_count);
        indicies_buffer[4 + (6 * face_count)] = 2 + (4 * face_count);
        indicies_buffer[5 + (6 * face_count)] = 3 + (4 * face_count);

        assignTextureCoords(face_count);
        face_count++;
    }

    // Left Face
    if (bit_mask & (1 << 5)) {  // Left face bit (assuming Left is the 6th bit, index 5)
        // Define the 4 vertices for the Left face (X = position->x)
        StaticRenderer::SetVertice(0 + (4 * face_count), 0 + position->x, 0 + position->y, 0 + position->z, vertex_buffer); // V0: (x,y,z) - bottom-back-left
        StaticRenderer::SetVertice(1 + (4 * face_count), 0 + position->x, 0 + position->y, 1 + position->z, vertex_buffer); // V1: (x,y,z+1) - bottom-front-left
        StaticRenderer::SetVertice(2 + (4 * face_count), 0 + position->x, 1 + position->y, 0 + position->z, vertex_buffer); // V2: (x,y+1,z) - top-back-left
        StaticRenderer::SetVertice(3 + (4 * face_count), 0 + position->x, 1 + position->y, 1 + position->z, vertex_buffer); // V3: (x,y+1,z+1) - top-front-left

        // Define the indices for the two triangles making up the face
        // *** REVERSED WINDING ORDER HERE ***

        // Triangle 1: V0, V2, V1 -> reversed to V1, V2, V0
        indicies_buffer[0 + (6 * face_count)] = 1 + (4 * face_count); // V1
        indicies_buffer[1 + (6 * face_count)] = 2 + (4 * face_count); // V2
        indicies_buffer[2 + (6 * face_count)] = 0 + (4 * face_count); // V0

        // Triangle 2: V1, V2, V3 -> reversed to V1, V3, V2  OR V3, V2, V1 (depending on preferred order)
        // Let's use V1, V3, V2 to maintain the common pattern from V1
        indicies_buffer[3 + (6 * face_count)] = 1 + (4 * face_count); // V1
        indicies_buffer[4 + (6 * face_count)] = 3 + (4 * face_count); // V3
        indicies_buffer[5 + (6 * face_count)] = 2 + (4 * face_count); // V2

        // --- Alternatively, you could reverse the second triangle differently, e.g., 3, 2, 1 ---
        // indicies_buffer[3 + (6 * face_count)] = 3 + (4 * face_count); // V3
        // indicies_buffer[4 + (6 * face_count)] = 2 + (4 * face_count); // V2
        // indicies_buffer[5 + (6 * face_count)] = 1 + (4 * face_count); // V1
        // --- Either reversal pair should fix the "inside out" issue ---


        assignTextureCoords(face_count);
        face_count++;
    }
    return face_count;  // Return the number of faces rendered
}