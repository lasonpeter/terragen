#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define ASIO_NO_WINDOWS_H
#define NOUSER
#define NOGDI
#define NODRAWTEXT
#define NOMCX
#define NOSHOWWINDOW
#define NOCLOSEWINDOW
#define VC_EXTRALEAN

#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include <iostream>
#include <bitset>
#include <vector>

#include "utilities/FaceMask.h"
#include "raymath.h"
#include "raygui.h"
#include "netcode/ProtoClient.h"
#include "FastNoise/FastNoise.h"
#include "netcode/generated/ChunkTransmitModel.pb.h"
#include "procedural/ChunkGovernor.h"
#include "procedural/terrain/BiomeGeneration.h"
#include "procedural/terrain/TerrainImage.h"
#include "rendering/StaticRenderer.h"
#include "rendering/chunks/ChunkRenderer.h"
#include "data/textures/blocks/blocks.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
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
    //movement and such
    float speed = 0.05f;
    float movement_speed = 1.0f;
    Vector3 camera_position = {1, 1, 1};
    const int ATLAS_SIZE=256;
    const int seed = 1337;
    const char *myEncodedTree2D = "GQAHAAENAAQAAAAAACBABwAAZmYmPwAAAAA/";
    const char *myEncodedTree3D = "EwCamZk+GgABEQACAAAAAADgQBAAAACIQR8AFgABAAAACwADAAAAAgAAAAMAAAAEAAAAAAAAAD8BFAD//wAAAAAAAD8AAAAAPwAAAAA/AAAAAD8BFwAAAIC/AACAPz0KF0BSuB5AEwAAAKBABgAAj8J1PACamZk+AAAAAAAA4XoUPw==";

    asio::io_context io_context;

    ProtoClient client(io_context);

    static std::vector<Chunk*> chunks;

    client.connectTcp("127.0.0.1", 7777);

    client.startReceiveTcp([](std::unique_ptr<google::protobuf::Message> msg) {
        // tutaj rzutujemy lub używamy refleksji
        if (auto login = dynamic_cast<terragen::LoginModel*>(msg.get())) {
            std::cout<<"Odebrano LOGIN: user="<<login->username()<<"\n";
        }
        else if (auto chunk = dynamic_cast<terragen::ChunkTransmitModel*>(msg.get()))
        {


            auto bytes = chunk->data();

            auto chunkId = chunk->id();

            auto pos = chunkId.find('_');
            int x = std::stoi(chunkId.substr(0, pos));
            int z = std::stoi(chunkId.substr(pos + 1));

            Int2 chunkPos = {x, z};



            std::vector<uint8_t> data;
            for (unsigned char c: bytes)
            {
                data.push_back(static_cast<uint8_t>(c));
            }

            std::vector<Block> enums;
            for (uint8_t b : data)
            {
                enums.push_back(Block(static_cast<BlockType>(b)));
            }

            Chunk* chunka = new Chunk(chunkPos);

            std::copy(enums.begin(), enums.end(), chunka->blocks);

            chunks.push_back(chunka);

        }
        else
        {
            std::cout<<"Odebrano coś\n";
        }
            //TODO: more models
        });

    std::thread ioThread([&]{ io_context.run(); });

    terragen::LoginModel login;

    login.set_username("Pixel");

    login.set_version(1);

    login.set_udpaddress("127.0.0.1");

    login.set_udpport(7777);

    client.sendMessageTcp(login, terragen::MessageType::LOGIN);



    std::this_thread::sleep_for(std::chrono::seconds(30));



    //ChunkGovernor chunkGovernor = ChunkGovernor();
    //chunkGovernor.GenerateChunks(seed, myEncodedTree2D, myEncodedTree3D);

    /*Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    Texture2D texturechecked = LoadTextureFromImage(checked);
    UnloadImage(checked);*/

    ChunkRenderer chunkRenderer= ChunkRenderer{};
    chunkRenderer.addChunksToBeRendered(&chunks,33);
    chunkRenderer.uploadMeshes();

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory

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
        chunkRenderer.renderChunks();
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

    return 0;
}