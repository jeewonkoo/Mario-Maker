//
// Created by 16182 on 2/23/2022.
//

#include "TileGrid.h"
#include <cassert>
#include <raymath.h>

void TileGrid::render(Vector2 top_left, Vector2 size) const {
    auto step = Vector2Divide(size, Vector2{static_cast<float>(width), static_cast<float>(height)});

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            auto left = Vector2Add(top_left, Vector2Multiply(step, {float(x), float(y)}));
            if(at(x,y).solid){
                //DrawRectangleV(left, step, RED);
                DrawTexturePro(tex, Rectangle{ 1, 205, 15, 15 }, Rectangle{ left.x, left.y, 64, 64 }, Vector2Subtract(left, Vector2Multiply({ static_cast<float>(x), static_cast<float>(y) }, { 64.f, 64.f })), 0, WHITE);
            } else {

            }
        }
    }
}

Tile TileGrid::at(int x, int y) const{
    if(x < 0 || x >= width || y < 0 || y >= height){
        return Tile{.solid = true};
    } else {
        return tiles[y * width + x];
    }
}


Tile &TileGrid::at_mut(int x, int y) {
    assert(!(x < 0 || x >= width || y < 0 || y >= height) && "out of bounds tile access");
    return tiles[y * width + x];
}

TileCollisionSet TileGrid::collide(Rectangle rect) const{
    int width_steps = std::ceil(rect.width);
    int height_steps = std::ceil(rect.height);
    int start_x = std::floor(rect.x);
    int start_y = std::floor(rect.y);

    TileCollisionSet collisions{};

    for(int dx = 0; dx <= width_steps; dx++){
        for(int dy = 0; dy <= height_steps; dy++){
            int x = start_x + dx;
            int y = start_y + dy;
            if(at(x,y).solid){
                auto collision = collide_grid(rect, x, y);
                if(collision.has_value()){
                    collisions.collisions.push_back(TileCollision{.tile = at(x,y), .collision = collision.value()});
                }
            }
        }
    }

    auto closest = std::max_element(collisions.collisions.begin(),  collisions.collisions.end(), [](auto & a, auto & b){
        return a.collision.area < b.collision.area;
    });

    if(closest != collisions.collisions.end()){
        collisions.eject_vector = {closest->collision.eject_vector};
    }

    return collisions;
}

std::optional<Collision> TileGrid::collide_grid(Rectangle rect, int x, int y) {
    Rectangle tile_rect = {float(x), float(y), 1, 1};
    return collide_rect(rect, tile_rect);
}

void TileGrid::resize(size_t width, size_t height) {
    tiles.resize(width * height);
    this->width = width;
    this->height = height;
}

