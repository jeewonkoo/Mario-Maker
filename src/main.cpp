#include <raylib.h>
#include "Level.h"
#include <cmath>
int main(){
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 1024;

    InitWindow(screenWidth, screenHeight, "Mario Maker");

    Image background = LoadImage("images/mario_background.png");
    Texture2D texture = LoadTextureFromImage(background);
    UnloadImage(background);

    int boxPositionY = screenHeight/2 - 40;
    int scrollSpeed = 4;            // Scrolling speed in pixels

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Level level;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            level.tiles[15-y][x] = rand() % (y+1) == 0;
        }
    }
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
        {
        // Update
        //----------------------------------------------------------------------------------
        boxPositionY -= (GetMouseWheelMove()*scrollSpeed);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(texture, 0, 0, WHITE);

        Vector2 top_left = {(float)0, (float)0};
        Vector2 bottom_right = {(float)screenWidth, (float)screenHeight};
         level.render(top_left, bottom_right);

        EndDrawing();
        //----------------------------------------------------------------------------------
        }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}