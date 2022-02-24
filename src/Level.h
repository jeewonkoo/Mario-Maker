//
// Created by 16182 on 2/23/2022.
//

#ifndef MARIO_MAKER_LEVEL_H
#define MARIO_MAKER_LEVEL_H

#include<array>
#include<raylib.h>
#include<random>
#include"Tile.h"

class Level {
public:
    Level(){
        for(int x = 0; x < 16; x++){
            for(int y = 0; y < 16; y++){
                tiles[15-y][x].solid = rand() % (y+1) == 0;
            }
        }
    };

    void render(Vector2 top_left, Vector2 bottom_right);
    Tile at(double x, double y);
private:
    static constexpr size_t width = 16;
    static constexpr size_t height = 16;
    std::array<std::array<Tile, width>, height> tiles{};
};


#endif //MARIO_MAKER_LEVEL_H
