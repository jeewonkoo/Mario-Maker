#ifndef MARIO_MAKER_TILE_H
#define MARIO_MAKER_TILE_H

#include<raylib.h>
#include<vector>
#include<optional>

#include<nlohmann/json.hpp>

struct Tile {
    bool solid{};
    Rectangle tex_src;
    nlohmann::json to_json() const {
        auto tile_json = nlohmann::json();
        tile_json["solid"] = solid;
        tile_json["x"] = tex_src.x;
        tile_json["y"] = tex_src.y;
        tile_json["w"] = tex_src.width;
        tile_json["h"] = tex_src.height;
        return tile_json;
    }

    static Tile from_json(const nlohmann::json & json){
        return {
            .solid = json.at("solid"),
            .tex_src = {
                .x = json.at("x"),
                .y = json.at("y"),
                .width = json.at("width"),
                .height = json.at("height")
            }
        };
    }
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
