//
// Created by 16182 on 2/23/2022.
//

#ifndef MARIO_MAKER_TILE_H
#define MARIO_MAKER_TILE_H


struct Tile {
    bool solid{};
};

enum class Side {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

#endif //MARIO_MAKER_TILE_H
