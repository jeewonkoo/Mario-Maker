#include <raylib.h>
#include "TileGrid.h"
#include "Mario.h"
#include "enemies/Goomba.h"
#include "enemies/Boo.h"
#include "enemies/Piranha.h"
#include "powerups/Mushroom.h"
#include "powerups/SmallShroom.h"
#include "Level.h"
#include "BuilderUI.h"

int main(){
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;                                       //set width size of screen
    const int screenHeight = 1024;                                      //set height size of screen

    InitWindow(screenWidth, screenHeight, "Mario Maker");               //initializing game graphic window

    Image background = LoadImage("images/mario_background.png");        //set background image
    Texture2D background_texture = LoadTextureFromImage(background);    //load background image to turn into texture
    UnloadImage(background);                                            //unload background image after turn into texture

    Image mario_img = LoadImage("images/mario_sprites.png");                   //set regular mario sprite
    Texture2D sprite_texture = LoadTextureFromImage(mario_img);          //load regular mario sprite to turn into texture
    UnloadImage(mario_img);                                             //unload regular mario sprite after turn into texture

    Image tile_img = LoadImage("images/mario_sprites_2.png");           //set tile sprite
    Texture2D tile_texture = LoadTextureFromImage(tile_img);            //load tile sprite to turn into texture
    UnloadImage(tile_img);                                              //unload tile sprite after turn into texture

    Image end_img = LoadImage("images/dead_screen.png");        //set end_screen image
    Texture2D end_texture = LoadTextureFromImage(end_img);    //load end_screen image to turn into texture
    UnloadImage(end_img);

    SetTargetFPS(60);                                                   // Set our game to run at 60 frames-per-second

    bool in_builder = false;
    Level level{tile_texture};
    BuilderUI ui(level, sprite_texture, tile_texture);

    auto m = std::make_unique<Mario>(10, 3, sprite_texture);
    Mario * mario = m.get();
    level.add_entity(std::move(m));
    level.set_focus_entity(mario);
    for(int i = 0; i < 16; i++){
        level.add_entity(std::make_unique<Mushroom>(i, 10, sprite_texture));
    }
    for (int i = 0; i < 16; i++) {
        level.add_entity(std::make_unique<SmallShroom>(i, 10, sprite_texture));
    }
    for (int i = 0; i < 16; i++) {
        level.add_entity(std::make_unique<Goomba>(i, 10, sprite_texture));
    }


    level.add_entity(std::make_unique<Boo>(5,10, sprite_texture,mario));

    for (int i = 0; i < 16; i++) {
        level.add_entity(std::make_unique<Piranha>(rand() % 30, rand() % 10, sprite_texture, mario));
    }

    // Main game loop
    while (!WindowShouldClose()){

        PollInputEvents();


        if(IsKeyDown(KEY_ENTER)) in_builder = !in_builder;

        InputState input {
            .left = IsKeyDown(KEY_LEFT),
            .right = IsKeyDown(KEY_RIGHT),
            .up = IsKeyDown(KEY_UP),
            .down = IsKeyDown(KEY_DOWN),
            .space = IsKeyDown(KEY_SPACE),
        };

        
        if(in_builder){
            ui.handle_events();
        } else {
            if (!mario->is_dead())
                level.update(input);
            else
                break;
        }

        Camera2D cam{};
        cam.rotation = 0;
        cam.offset = Vector2Add(Vector2Multiply(level.get_camera_offset(), {-64.f, -64.f}), {512, 0});
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

        if(in_builder) ui.render({0,0}, {screenWidth, screenHeight});

        EndDrawing();

    }

    while (!WindowShouldClose()) {
        // dead screen
        BeginDrawing();
        {
            Camera2D cam{};
            cam.rotation = 0;
            cam.offset = {0, 0};
            cam.target = { 0,0 };
            cam.zoom = 1.0;

            ClearBackground(RAYWHITE);
            BeginMode2D(cam);
            {
                DrawTextureTiled(end_texture, { 0, 0, 512,512 }, { 512,512 }, { 0,0 }, 0, 1, WHITE);
            }
            EndMode2D();
        }
        EndDrawing();
    }


    CloseWindow();                                                      // Close window and OpenGL context

    return 0;
}