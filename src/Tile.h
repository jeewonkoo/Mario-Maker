#ifndef MARIO_MAKER_TILE_H
#define MARIO_MAKER_TILE_H

#include<raylib.h>
#include<vector>
#include<optional>

struct Tile {
    bool solid{};
};

enum class Side {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

struct Collision {
    Side collision_side;
    Vector2 eject_vector;
    float area;
};

struct TileCollision {
    Tile tile;
    Collision collision;
};

struct TileCollisionSet {
    std::vector<TileCollision> collisions;
    std::optional<Vector2> eject_vector;
};

#endif //MARIO_MAKER_TILE_H
