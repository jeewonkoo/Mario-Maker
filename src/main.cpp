#include <raylib.h>
#include "Level.h"
#include "Mario.h"
#include "Villain.h"
#include "Goomba.h"
#include <cmath>
int main(){
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 1024;

    InitWindow(screenWidth, screenHeight, "Mario Maker");

    Image background = LoadImage("images/mario_background.png");
    Texture2D background_texture = LoadTextureFromImage(background);
    UnloadImage(background);

    Image page2 = LoadImage("images/mario_sprites2.png");
    Texture2D page2_texture = LoadTextureFromImage(page2);
    UnloadImage(page2);

    Image mario_img = LoadImage("images/marios.png");
    Texture2D mario_texture = LoadTextureFromImage(mario_img);
    UnloadImage(mario_img);


    Image goomba_img = LoadImage("images/goomba.png");
    Texture2D goomba_texture = LoadTextureFromImage(goomba_img);
    UnloadImage(goomba_img);

    Image tile_img = LoadImage("images/mario_sprites_2.png");
    Texture2D tile_texture = LoadTextureFromImage(tile_img);
    UnloadImage(tile_img);


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Level level(tile_texture, 100, 16);


    Mario mario(10,10, mario_texture);
    Goomba goomba(10, 10, goomba_texture);

    // Main game loop
    while (!WindowShouldClose()){

        PollInputEvents();

        bool left = IsKeyDown(KEY_LEFT);
        bool right = IsKeyDown(KEY_RIGHT);
        bool up = IsKeyDown(KEY_UP);
        bool down = IsKeyDown(KEY_DOWN);
        bool space = IsKeyDown(KEY_SPACE);

        goomba.update(level);
        mario.update(level, left, right, up, down, space);
        Camera2D cam{};
        cam.rotation = 0;
        cam.offset = {mario.rect().x * -64 + 512,0};
        cam.target = {0,0};
        cam.zoom = 1.0;

        BeginDrawing();

            ClearBackground(RAYWHITE);
        BeginMode2D(cam);

//            DrawTexture(background_texture, 0, 0, WHITE);
            DrawTextureTiled(background_texture, {0, 0, 1024,1024}, {0, 0, 4*1024,1024},{mario.rect().x * -30,0},0,1,WHITE);
            Vector2 top_left = {(float)0, (float)0};
            Vector2 bottom_right = {(float)screenWidth, (float)screenHeight};
            level.render(top_left, bottom_right);

            goomba.render(top_left, bottom_right, 0, 0, 0, 0);
            mario.render(top_left, bottom_right);
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}