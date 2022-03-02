//
// Created by 16182 on 3/2/2022.
//

#ifndef MARIO_MAKER_LEVEL_H
#define MARIO_MAKER_LEVEL_H

#include "TileGrid.h"
#include "Entity.h"
#include "InputState.h"
#include<memory>


class Level {
public:
    explicit Level(Texture tileset_texture): grid(tileset_texture, 100, 16){}
    void update(InputState keyboard_input);
    void render(Vector2 top_left, Vector2 size);
    Vector2 camera_center() const;
    void add_entity(std::unique_ptr<Entity> ent) {
        entities.push_back(std::move(ent));
    }
private:
    TileGrid grid;
    std::vector<std::unique_ptr<Entity>> entities;
};


#endif //MARIO_MAKER_LEVEL_H
