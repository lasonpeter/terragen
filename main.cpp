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
    const int screenWidth = 800;
    const int screenHeight = 450;
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
    Vector3 camera_position = {0, 0, 0};



    auto fnSimplex = FastNoise::New<FastNoise::CellularValue>();
    auto fnFractal = FastNoise::New<FastNoise::FractalFBm>();
    auto somethin = FastNoise::NewFromEncodedNodeTree("EQACAAAAAAAgQBAAAAAAQBkAEwDD9Sg/DQAEAAAAAAAgQAkAAGZmJj8AAAAAPwEEAAAAAAAAAEBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM3MTD4AMzMzPwAAAAA/");

    /*fnFractal->SetSource( fnSimplex );
    fnFractal->SetOctaveCount( 5 );*/

    const int ATLAS_SIZE=256;
    std::vector<float> noiseOutput(ATLAS_SIZE * ATLAS_SIZE *ATLAS_SIZE);
    // Generate a 16 x 16 x 16 area of noise
    //FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree( "EwDNzEw+GQAbAA0ABAAAAAAAAEAHAAAK1yM/AAAAAAAA16MQQAEJAA==" );
    int index = 0;
    //image.data = noiseOutput.data();

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


    Mesh mesh = { 0 };
    mesh.triangleCount = 12;
    mesh.vertexCount = 4*6;
    mesh.vertices = new float[mesh.vertexCount*3];    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = new float[mesh.vertexCount*2];   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = new float[mesh.vertexCount*3];     // 3 vertices, 3 coordinates each (x, y, z)
    mesh.indices = new unsigned short[mesh.triangleCount*3];

 /*   //TOP FACE
    StaticRenderer::SetVertice(0, 0,1, 0,mesh.vertices);
    StaticRenderer::SetVertice(1, 1,1, 0,mesh.vertices);
    StaticRenderer::SetVertice(2, 0,1, 1,mesh.vertices);
    StaticRenderer::SetVertice(3, 1,1, 1,mesh.vertices);

    //RIGHT TRIANGLE
    mesh.indices[0] = 3;
    mesh.indices[1] = 1;
    mesh.indices[2] = 0;

    //LEFT TRIANGLE
    mesh.indices[3] = 2;
    mesh.indices[4] = 3;
    mesh.indices[5] = 0;
    //TEXTURES
    mesh.texcoords[0] = 1; //X
    mesh.texcoords[1] = 0; //Y

    mesh.texcoords[2] = 0; //X
    mesh.texcoords[3] = 0; //Y

    mesh.texcoords[4] = 1; //X
    mesh.texcoords[5] = 1; //Y

    mesh.texcoords[6] = 0; //X
    mesh.texcoords[7] = 1; //Y
    
    //BOTTOM FACE
    StaticRenderer::SetVertice(0+4, 0,0, 0,mesh.vertices);
    StaticRenderer::SetVertice(1+4, 1,0, 0,mesh.vertices);
    StaticRenderer::SetVertice(2+4, 0,0, 1,mesh.vertices);
    StaticRenderer::SetVertice(3+4, 1,0, 1,mesh.vertices);

    //RIGHT TRIANGLE
    mesh.indices[0+6] = 0+4;
    mesh.indices[1+6] = 1+4;
    mesh.indices[2+6] = 3+4;
    //LEFT TRIANGLE
    mesh.indices[3+6] = 0+4;
    mesh.indices[4+6] = 3+4;
    mesh.indices[5+6] = 2+4;
    //TEXTURES
    mesh.texcoords[0+8] = 1; //X
    mesh.texcoords[1+8] = 0; //Y

    mesh.texcoords[2+8] = 0; //X
    mesh.texcoords[3+8] = 0; //Y

    mesh.texcoords[4+8] = 1; //X
    mesh.texcoords[5+8] = 1; //Y

    mesh.texcoords[6+8] = 0; //X
    mesh.texcoords[7+8] = 1; //Y
*/

 uint8_t face_mask{};
 face_mask = face_mask+ FaceMask::Top;
 face_mask = face_mask+ FaceMask::Bottom;
 face_mask = face_mask+ FaceMask::Left;
 face_mask = face_mask+ FaceMask::Right;
 face_mask = face_mask+ FaceMask::Front;
 face_mask = face_mask+ FaceMask::Back;
 std::bitset<8> b(face_mask);

    std::cout<<b<<std::endl;
 int face_count{};
 face_count =StaticRenderer::RenderCube(face_mask, mesh.vertices,mesh.indices,mesh.texcoords,mesh.normals,new Int3{0,0,0},face_count);
 face_count =StaticRenderer::RenderCube(face_mask, mesh.vertices,mesh.indices,mesh.texcoords,mesh.normals,new Int3{1,0,0},face_count);
 face_count =StaticRenderer::RenderCube(face_mask, mesh.vertices,mesh.indices,mesh.texcoords,mesh.normals,new Int3{1,0,1},face_count);
 mesh.triangleCount = face_count*2;
 mesh.vertexCount = face_count*4;
    //NORMALS
    for (int i = 0; i <= mesh.vertexCount; i=i+3) {
        std::cout<<i<<std::endl;
        mesh.normals[i] = 0;
        mesh.normals[i+1] = 1;
        mesh.normals[i+2] = 0;
    }


    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);



    Texture2D texture = LoadTextureFromImage(image);

    SetExitKey(KEY_ESCAPE);
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
        /*for (int z = 0; z < ATLAS_SIZE; z++){
            for (int y = 0; y < ATLAS_SIZE; y++)
            {
                for (int x = 0; x < ATLAS_SIZE; x++)
                {
                    //std::cout<<noiseOutput[y*ATLAS_SIZE + x] <<" ";
                    if (noiseOutput[z*ATLAS_SIZE+y*ATLAS_SIZE + x] > 0.0f)
                    {
                        DrawCubeWires( Vector3(x, y, z), .5f, .5f, .5f,BLACK);
                    }

                }
            }
        }*/
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