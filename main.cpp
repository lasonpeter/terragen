#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include <iostream>
#include <bitset>
#include <chrono>

#include "utilities/FaceMask.h"
#include "raymath.h"
#include "raygui.h"
#include "FastNoise/FastNoise.h"
#include "procedural/ChunkGovernor.h"
#include "procedural/terrain/BiomeGeneration.h"
#include "procedural/terrain/TerrainImage.h"
#include "rendering/StaticRenderer.h"
#include "rendering/chunks/ChunkRenderer.h"
#include "data/textures/blocks/blocks.h"
#include "physics/PhysiscsGovernor.h"
#include "physics/ChunkCollisionManager.h"
#include "scripts/Player.h"
#include "ECBS/components/RigidBody.h"
#include "ECBS/components/Collider.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800*1.5;
    const int screenHeight = 450*1.5;
    InitWindow(screenWidth, screenHeight, "terragen");
    Camera3D camera = {0};
    camera.position = Vector3{1.0f, 150.0f, 1.0f}; // Camera position
    camera.target = Vector3{0.0f, 0.0f, 0.0f}; // Camera looking at point
    camera.up = Vector3{0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
    camera.fovy = 70.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);
    SetTraceLogLevel(LOG_ERROR);
    //movement and such
    float speed = 0.05f;
    float movement_speed = 0.8f;
    Vector3 camera_position = {1, 1, 1};
    const int ATLAS_SIZE=256;
    const int seed = 767867547567;
    const char *myEncodedTree2D = "GQAHAAENAAQAAAAAACBABwAAZmYmPwAAAAA/";
    const char *myEncodedTree3D = "EwCamZk+GgABEQACAAAAAADgQBAAAACIQR8AFgABAAAACwADAAAAAgAAAAMAAAAEAAAAAAAAAD8BFAD//wAAAAAAAD8AAAAAPwAAAAA/AAAAAD8BFwAAAIC/AACAPz0KF0BSuB5AEwAAAKBABgAAj8J1PACamZk+AAAAAAAA4XoUPw==";

    ChunkGovernor chunkGovernor = ChunkGovernor();
    chunkGovernor.GenerateChunks(seed, myEncodedTree2D, myEncodedTree3D);

    /*Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    Texture2D texturechecked = LoadTextureFromImage(checked);
    UnloadImage(checked);*/

    ChunkRenderer chunkRenderer= ChunkRenderer();
    chunkRenderer.loadTextureAtlas();
    ChunkCache chunkCache = ChunkCache(&chunkRenderer);
    chunkCache.chunkGovernor = chunkGovernor;
    chunkRenderer.addChunkCache(&chunkCache);

    PhysiscsGovernor::GetInstance()->Start();

    Player player = Player();
    player.camera = camera; // Set the camera reference
    player.AddComponent<ECBS::RigidBody>();
    player.AddComponent<ECBS::Collider>();
    player.GetComponent<ECBS::Collider>()->boundingBox = BoundingBox{Vector3{0,0,0}, Vector3{1,1,1}};

    // Create chunk collision manager
    ChunkCollisionManager chunkCollisionManager(&chunkGovernor, &player);
    
    // Register collision update function with physics governor
    PhysiscsGovernor::GetInstance()->AddPhysicsFunction([&chunkCollisionManager](float deltaTime) {
        chunkCollisionManager.UpdateCollisions(deltaTime);
    });
    
    // Register player update function
    PhysiscsGovernor::GetInstance()->AddPhysicsFunction([&player, &camera](float deltaTime) {
        player.camera = camera; // Update camera reference each physics tick
        player.fixedDeltaTime(deltaTime);
    });


// Register physics functions

// Start the physics thread

// Later, when done

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory

    SetExitKey(KEY_ESCAPE);
    HideCursor();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    int x=0;
    int i=0;
    int max=chunkGovernor.chunks_.size();
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(max > i){

            // Only add one chunk per frame to reduce stuttering
            chunkCache.addChunk(chunkGovernor.chunks_[i]);
            i++;
        }
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
        
        auto renderStart = std::chrono::high_resolution_clock::now();
        chunkRenderer.renderChunks();
        auto renderEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> renderTime = renderEnd - renderStart;
        if (renderTime.count() > 16.0) { // Only log if rendering takes more than 16ms (60fps threshold)
            std::cout << "Chunk rendering time: " << renderTime.count() << "ms" << std::endl;
        }
        /*Model model= LoadModelFromMesh(mesh);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texturechecked;
        DrawModel(model, Vector3{0, 0, 0}, 1.0f, WHITE);*/

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

        DrawCubeWires( Vector3{0,0,0}, .5f, .5f, .5f,BLACK);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    PhysiscsGovernor::GetInstance()->Stop();
    return 0;
}