//
// Created by 16182 on 3/2/2022.
//

#include "Level.h"

void Level::update(InputState keyboard_input) {
    for(auto & e : entities){
        e->update(grid, keyboard_input);
    }
}

void Level::render(Vector2 top_left, Vector2 size) {
    grid.render(top_left, size);
    for(auto & e : entities){
        e->render(top_left, size);
    }
}

Vector2 Level::camera_center() const {
    return {0, 0};
}
