//
// Created by 16182 on 2/23/2022.
//

#include "TileGrid.h"
#include <cassert>
#include <raymath.h>

/**
 * Renders(draw) tile grids on graphic. Accepts two Vector2 as parameters
 * 
 * @param top_left top left location of tile grid on graphic 
 * @param size size of tile grid on graphic 
 */
void TileGrid::render(Vector2 top_left, Vector2 size) const {
    auto step = Vector2Divide(size, Vector2{static_cast<float>(width), static_cast<float>(height)});

    for(size_t y = 0; y < height; y++){
        for(size_t x = 0; x < width; x++){
            auto left = Vector2Add(top_left, Vector2Multiply(step, {float(x), float(y)}));
            if(at(x,y).solid){
                //DrawRectangleV(left, step, RED);
                DrawTexturePro(tex, Rectangle{ 1, 205, 15, 15 }, Rectangle{ left.x, left.y, 64, 64 }, Vector2Subtract(left, Vector2Multiply({ static_cast<float>(x), static_cast<float>(y) }, { 64.f, 64.f })), 0, WHITE);
            } else {

            }
        }
    }
}

/**
 * Returns tile grid on given location x and y on graphic
 * 
 * @param x x axis coordinate 
 * @param y y axis coordinate
 * @return tile grid on x and y parameter
 */
Tile TileGrid::at(int x, int y) const{
    if(x < 0 || x >= (int)width || y < 0 || y >= (int)height){
        return Tile{.solid = true};
    } else {
        return tiles[y * width + x];
    }
}

/**
 * Modifies tile grid with given x and y 
 * 
 * @param x x axis coordinate
 * @param y y axis coordinate
 * @return modified tile grid 
 */
Tile &TileGrid::at_mut(int x, int y) {
    assert(!(x < 0 || x >= (int)width || y < 0 || y >= (int)height) && "out of bounds tile access");
    return tiles[y * width + x];
}

/**
 * Collides rectangle against the level geometry. Determines if tile collides with other entity.
 * 
 *  @param rect rectangle that collides against tile grid 
 *  @return array of collided tile
 */
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

/**
 * Collides rectangle against the level geometry. Determines if tile collides with other entity.
 * Indicates if the value is initialized or not using std::optional 
 * 
 * @param rect rectangle that collides against tile grid 
 * @param x x axis coordinate
 * @param y y axis coordinate
 * @return collided rectangle
 */
std::optional<Collision> TileGrid::collide_grid(Rectangle rect, int x, int y) {
    Rectangle tile_rect = {float(x), float(y), 1, 1};
    return collide_rect(rect, tile_rect);
}

/**
 * resize size of tile grid with given width and height parameters
 * 
 * @param width Width of new tile grid
 * @param height Height of new tile grid
 */
void TileGrid::resize(size_t width, size_t height) {
    tiles.resize(width * height);
    this->width = width;
    this->height = height;
}

