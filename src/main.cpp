#include <raylib.h>
#include "TileGrid.h"
#include "Mario.h"
#include "enemies/Goomba.h"
#include "enemies/Boo.h"
#include "powerups/Mushroom.h"
#include "Level.h"

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

    Image boo_img = LoadImage("images/Boo_opened.png");
    Texture2D boo_texture = LoadTextureFromImage(boo_img);
    UnloadImage(boo_img);

    Image mushroom_img = LoadImage("images/mushroom.png");
    Texture2D mushroom_texture = LoadTextureFromImage(mushroom_img);
    UnloadImage(mushroom_img);


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


    Level level{tile_texture};

    auto m = std::make_unique<Mario>(10, 3, mario_texture);
    Mario * mario = m.get();
    level.add_entity(std::move(m));
    for(int i = 0; i < 16; i++){
        level.add_entity(std::make_unique<Mushroom>(i, 10, mushroom_texture));
    }
    //for (int i = 0; i < 16; i++) {
    //    level.add_entity(std::make_unique<Goomba>(i, 10, goomba_texture));
    //}


    //level.add_entity(std::make_unique<Boo>(5,10,boo_texture,mario));

    // Main game loop
    while (!WindowShouldClose()){

        PollInputEvents();

        InputState input {
            .left = IsKeyDown(KEY_LEFT),
            .right = IsKeyDown(KEY_RIGHT),
            .up = IsKeyDown(KEY_UP),
            .down = IsKeyDown(KEY_DOWN),
            .space = IsKeyDown(KEY_SPACE),
        };

        level.update(input);
        Camera2D cam{};
        cam.rotation = 0;
        cam.offset = {mario->rect().x * -64 + 512, 0};
        cam.target = {0,0};
        cam.zoom = 1.0;

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            BeginMode2D(cam);
            {
                // draw mountains
                float paralax_mountains = mario->rect().x * -40;
                float paralax_clouds = mario->rect().x * -53;

                DrawTextureTiled(background_texture, {0, 512, 1024,512}, {-1024, 512, 6*1024,512},{paralax_mountains,0},0,1,WHITE);
                DrawTextureTiled(background_texture, {0, 0, 1024,512}, {-1024, 0, 6*1024,512},{paralax_clouds,0},0,1,WHITE);
                Vector2 top_left = {(float)0, (float)0};
                Vector2 bottom_right = {(float)screenWidth, (float)screenHeight};


                level.render(top_left, bottom_right);

            }
            EndMode2D();
        }
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}