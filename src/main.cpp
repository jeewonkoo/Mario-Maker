/*******************************************************************************************
*
*   raylib [core] examples - Mouse wheel input
*
*   This test has been created using raylib 1.1 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <raylib.h>
#include "Level.h"
#include <cmath>
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input mouse wheel");

    int boxPositionY = screenHeight/2 - 40;
    int scrollSpeed = 4;            // Scrolling speed in pixels

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Level level;
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            level.tiles[x][y] = rand() % 2;
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

        Vector2 top_left = {(float)0, (float)0};
        Vector2 bottom_right = {(float)100, (float)100};
        level.render(top_left, bottom_right);
//        DrawRectangle(screenWidth/2 - 40, boxPositionY, 80, 80, MAROON);
//
//        DrawText("Use mouse wheel to move the cube up and down!", 10, 10, 20, GRAY);
//        DrawText(TextFormat("Box position Y: %03i", boxPositionY), 10, 40, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
        }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}