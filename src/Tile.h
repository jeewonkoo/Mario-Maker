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

inline std::optional<Collision> collide_rect(Rectangle from, Rectangle against){
    // less than 0 means inside
    float left = -against.x - against.width + from.x;
    float right = -from.x - from.width + against.x;
    float top = -against.y - against.height + from.y;
    float bottom = -from.y - from.height + against.y;
    float closest = std::max({right, left, top, bottom});



    if(closest >= 0) return std::nullopt;


    float x_dist = std::min(std::abs(from.x - against.x - against.width), std::abs(against.x - from.x - from.width));
    float y_dist = std::min(std::abs(from.y - against.y - against.height), std::abs(against.y - from.y - from.height));
    float area = x_dist * y_dist;


    if(closest == left) return {Collision{ Side::LEFT, Vector2{-left, 0}, area}};
    if(closest == right) return {Collision{ Side::RIGHT, Vector2{right, 0}, area}};
    if(closest == top) return {Collision{ Side::TOP, Vector2{0, -top}, area}};
    if(closest == bottom) return {Collision{ Side::BOTTOM, Vector2{0, bottom}, area}};

    return std::nullopt;
}

#endif //MARIO_MAKER_TILE_H
