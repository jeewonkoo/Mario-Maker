//
// Created by 16182 on 2/23/2022.
//

#ifndef MARIO_MAKER_LEVEL_H
#define MARIO_MAKER_LEVEL_H

#include<array>
#include<raylib.h>
#include<random>
#include<optional>
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

    void render(Vector2 top_left, Vector2 bottom_right) const;
    Tile at(int x, int y) const;
    //collides rectangle against the level geometry
    TileCollisionSet collide(Rectangle rect) const;
private:
    static std::optional<Collision> collide_grid(Rectangle rect, int x, int y) ;
    static constexpr size_t width = 16;
    static constexpr size_t height = 16;
    std::array<std::array<Tile, width>, height> tiles{};

    static std::optional<Collision> collide_rectangle(Rectangle from, Rectangle against) ;
};


#endif //MARIO_MAKER_LEVEL_H
