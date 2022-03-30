//
// Created by 16182 on 3/2/2022.
//

#ifndef MARIO_MAKER_LEVEL_H
#define MARIO_MAKER_LEVEL_H

#include "TileGrid.h"
#include "Entity.h"
#include "InputState.h"
#include<memory>
#include<nlohmann/json.hpp>


class Level {
public:
    explicit Level(Texture tileset_texture): grid(tileset_texture, 100, 16){}
    void update(InputState keyboard_input);
    void render(Vector2 top_left, Vector2 size);
    void add_entity(std::unique_ptr<Entity> ent) {
        entities.push_back(std::move(ent));
    }
    void set_tile(int x, int y, Tile tile){
        grid.at_mut(x,y) = tile;
    }
    void set_focus_entity(Entity * entity){
        focus_entity = entity;
    }
    Vector2 get_camera_offset(){
        if(focus_entity){
            auto r = focus_entity->rect();
            return {r.x + r.width / 2, 0};
        } else {
            return {0,0};
        }
    }

    nlohmann::json to_json();
    static Level from_json(const nlohmann::json &json, Texture tex);

private:
    Level(const nlohmann::json& grid_json, const nlohmann::json& entities_json, Texture tex);
    TileGrid grid;
    std::vector<std::unique_ptr<Entity>> entities;
    Entity * focus_entity;
};


#endif //MARIO_MAKER_LEVEL_H
