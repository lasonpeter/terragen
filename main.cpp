#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include <iostream>
#include <bitset>

#include "utilities/FaceMask.h"
#include "raymath.h"
#include "raygui.h"
#include "FastNoise/FastNoise.h"
#include "procedural/terrain/BiomeGeneration.h"
#include "rendering/StaticRenderer.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800*1.5;
    const int screenHeight = 450*1.5;
    InitWindow(screenWidth, screenHeight, "terragen");
    Camera3D camera = {0};
    camera.position = Vector3{1.0f, 1.0f, 1.0f}; // Camera position
    camera.target = Vector3{0.0f, 0.0f, 0.0f}; // Camera looking at point
    camera.up = Vector3{0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
    camera.fovy = 70.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);
    //movement and such
    float speed = 0.05f;
    float movement_speed = 0.2f;
    Vector3 camera_position = {1, 1, 1};


    auto fnSimplex = FastNoise::New<FastNoise::CellularValue>();
    auto fnFractal = FastNoise::New<FastNoise::FractalFBm>();

    const int ATLAS_SIZE=32;
    std::vector<float> noiseOutput(ATLAS_SIZE * ATLAS_SIZE *ATLAS_SIZE);
    int index = 0;
    BiomeGeneration biome_generation= BiomeGeneration(12312);
    biome_generation.generateNoise(noiseOutput.data(),ATLAS_SIZE,0,0);

    Color* noisePixels = new Color[ATLAS_SIZE*ATLAS_SIZE];

    for (int y = 0; y < ATLAS_SIZE; y++)
    {
        for (int x = 0; x < ATLAS_SIZE; x++)
        {
            //std::cout<<noiseOutput[y*ATLAS_SIZE + x] <<" ";
            noisePixels[ATLAS_SIZE*y + x] = Color((noiseOutput[y*ATLAS_SIZE + x]+1)*127,0,0,255);
        }
    }

    Image image = Image(noisePixels,ATLAS_SIZE, ATLAS_SIZE);
    image.data=noisePixels;
    image.width = ATLAS_SIZE;
    image.height = ATLAS_SIZE;
    image.format= PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    image.mipmaps = 1;

    Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    Texture2D texturechecked = LoadTextureFromImage(checked);
    UnloadImage(checked);

    int face_count{};

     Chunk chunk = Chunk(Int2{0,0});
     chunk.blocks[0] = Block(BlockType::AIR);
    chunk.blocks[1] = Block(BlockType::DIRT);
    chunk.blocks[2] = Block(BlockType::DIRT);
    chunk.blocks[16] = Block(BlockType::DIRT);
    chunk.blocks[3] = Block(BlockType::DIRT);
    chunk.blocks[65535] = Block(BlockType::DIRT);

    int *amount_of_faces = new int;
    *amount_of_faces = 0;
    uint8_t* chunkFaceMasks = Chunk::generateChunkFaceMasks(&chunk,amount_of_faces);
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
                if(is_transparent(chunk.blocks[y*256+x*16+z].blockType)){
                    continue;
                }
                std::bitset<8> a(chunkFaceMasks[y*256+x*16+z]);

                std::cout<<a<<std::endl;
                face_count =StaticRenderer::RenderCube(chunkFaceMasks[y*256+x*16+z], mesh.vertices,mesh.indices,mesh.texcoords,mesh.normals,new Int3{x,y,z},face_count);
            }
        }
    }

    for (int i = 0; i <= mesh.vertexCount; i=i+3) {
        std::cout<<i<<std::endl;
        mesh.normals[i] = 0;
        mesh.normals[i+1] = 1;
        mesh.normals[i+2] = 0;
    }

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);



    Texture2D texture = LoadTextureFromImage(image);

    SetExitKey(KEY_NULL);
    HideCursor();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        ///
        ///TEMPORARY CAMERA MOVEMENT
        ///
        ///
        Vector3 camera_change = {0, 0, 0};
        if (IsKeyDown(KEY_W)) {
            camera_change.z = 1;
        }
        if (IsKeyDown(KEY_S)) {
            camera_change.z = 1;
        }
        if (IsKeyDown(KEY_A)) {
            camera_change.x = 1;
        }
        if (IsKeyDown(KEY_D)) {
            camera_change.x = 1;
        }
        if (IsKeyDown(KEY_SPACE)) {
            camera_change.y = 1;
        }

        Vector3 camera_move = {0, 0, 0};

        camera_move = {
                GetMouseDelta().x * speed, // Rotation: yaw
                GetMouseDelta().y * speed, // Rotation: pitch
                0.0f // Rotation: roll
        };
        SetMousePosition(GetRenderWidth() / 2, GetRenderHeight() / 2);
        ClearBackground(WHITE);
        Vector3Scale(camera_change, speed);
        camera_position = Vector3Add(camera_position, camera_change);
        UpdateCameraPro(&camera,
                        Vector3{
                                (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * movement_speed - // Move forward-backward
                                (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * movement_speed,
                                (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * movement_speed - // Move right-left
                                (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * movement_speed,
                                -(IsKeyDown(KEY_C)) * movement_speed + (IsKeyDown(KEY_SPACE)) * movement_speed
                                // Move up-down
                        }, camera_move,
                        GetMouseWheelMove() * 2.0f);

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        Model model= LoadModelFromMesh(mesh);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texturechecked;
        DrawModel(model, Vector3{0, 0, 0}, 1.0f, WHITE);

        // 0 [0,0,0)
        DrawCubeWires({0,0,0},0.2f, .2f, .2f,YELLOW);
        // 1 [1,0,0]            2     2     2
        DrawCubeWires({1,0,0},0.2f, .2f, .2f,ORANGE);
        // 3 [1,0,1]            2     2     2
        DrawCubeWires({1,0,1},0.2f, .2f, .2f,BLUE);
        // 2 [0,0,1]            2     2     2
        DrawCubeWires({0,0,1},0.2f, .2f, .2f,RED);

        DrawCubeWires({0,1,0},0.2f, .2f, .2f,VIOLET);




        DrawLine3D({0,0,0},{0,5,0}, BLUE);
        DrawLine3D({0,0,0},{0,0,5}, GREEN);
        DrawLine3D({0,0,0},{5,0,0}, RED);

        EndMode3D();
        DrawTexture(texture, screenWidth - texture.width - 20, 20, WHITE);

        DrawCubeWires( Vector3{0,0,0}, .5f, .5f, .5f,BLACK);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}