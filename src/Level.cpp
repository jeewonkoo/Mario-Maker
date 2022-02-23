//
// Created by 16182 on 2/23/2022.
//

#include "Level.h"
#include <raymath.h>

void Level::render(Vector2 top_left, Vector2 size) {
    auto step = Vector2Divide(size, {(float)tiles.size(), (float)tiles[0].size()});

    for(int y = 0; y < tiles.size(); y++){
        for(int x = 0; x < tiles[y].size(); x++){
            auto left = Vector2Add(top_left, Vector2Multiply(step, {float(x), float(y)}));
            if(tiles[y][x].solid){
                DrawRectangleV(left, step, RED);
            } else {

            }
        }
    }
}

Tile Level::at(double x, double y) {
    auto grid_x = (size_t)x;
    auto grid_y = (size_t)y;
    if(grid_x < 0 || grid_x >= width || grid_y < 0 || grid_y >= height){
        return Tile{.solid = true};
    } else {
        return tiles[grid_y][grid_x];
    }
}
