//
// Created by 16182 on 2/23/2022.
//

#ifndef MARIO_MAKER_TILEGRID_H
#define MARIO_MAKER_TILEGRID_H

#include<raylib.h>
#include<array>
#include<random>
#include<optional>
#include"Tile.h"

class TileGrid {
    public:
        TileGrid(Texture texture, size_t width, size_t height) {
            resize(width, height);
            tex = texture;

            for(size_t x = 0; x < width; x++){
    //            at_mut(x, height - 1).solid = true;
                for(size_t y = 0; y < height; y++){
                    at_mut(x, height - 1 - y).solid = rand() % (y+1) == 0;
                }
            }
        };

        void render(Vector2 top_left, Vector2 bottom_right) const;
        Tile at(int x, int y) const;
        Tile & at_mut(int x, int y);
        TileCollisionSet collide(Rectangle rect) const;
    private:
        void resize(size_t width, size_t height);
        static std::optional<Collision> collide_grid(Rectangle rect, int x, int y) ;
        size_t width;
        size_t height;
        std::vector<Tile> tiles{};
        Texture tex;
};


#endif //MARIO_MAKER_TILEGRID_H
