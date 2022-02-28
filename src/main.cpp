#include <raylib.h>
#include "Level.h"
#include "Mario.h"
#include "Villain.h"
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


    Image goomba_img = LoadImage("image/25685.png");
    Texture2D goomba_texture = LoadTextureFromImage(goomba_img);
    UnloadImage(goomba_img);

    Image tile_img = LoadImage("images/mario_sprites_2.png");
    Texture2D tile_texture = LoadTextureFromImage(tile_img);
    UnloadImage(tile_img);


    //DrawTextureQuad(page2_texture, )

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Level level(tile_texture);


    Mario mario(10,10, mario_texture);
    Villain goomba(10, 0, goomba_texture);

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
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(background_texture, 0, 0, WHITE);

            Vector2 top_left = {(float)0, (float)0};
            Vector2 bottom_right = {(float)screenWidth, (float)screenHeight};
            level.render(top_left, bottom_right);

            goomba.render(top_left, bottom_right);
            mario.render(top_left, bottom_right);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}