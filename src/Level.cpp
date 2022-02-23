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
            if(tiles[y][x]){
                DrawRectangleV(left, step, RED);
            } else {
                DrawRectangleV(left, step, BLUE);
            }
        }
    }
}
