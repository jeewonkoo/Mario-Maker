//
// Created by 16182 on 3/2/2022.
//

#include "Level.h"

void Level::update(InputState keyboard_input) {
    for(auto & e : entities){
        e->update(grid, keyboard_input);
    }

    for(auto & e1 : entities){
        for(auto & e2 : entities){
            if(&e1 != &e2){
                if(auto collision = collide_rect(e1->rect(),e2->rect()); collision.has_value()){
                    e1->on_collide({ .other = *e2, .side = collision->collision_side});
                }
            }
        }
    }

    entities.erase(std::remove_if(entities.begin(),  entities.end(), [](auto & e){ return e->should_remove();}), entities.end());
}

void Level::render(Vector2 top_left, Vector2 size) {
    grid.render(top_left, size);
    for(auto & e : entities){
        Rectangle r = e->rect();
        Vector2 pos = {r.x * 64, r.y * 64};
        Vector2 size = {r.width * 64, r.height * 64};
        DrawRectangleV(pos, size, GREEN);
    }
    for(auto & e : entities){
        e->render(top_left, size);
    }
}

nlohmann::json Level::to_json() {
    auto json = nlohmann::json{};
    json["tiles"] = std::move(grid.to_json());
    json["entities"] = nlohmann::json::array();
    return json;
}

Level Level::from_json(const nlohmann::json &json, Texture tex) {
    return {json["tiles"], json["entities"], tex};
}

Level::Level(const nlohmann::json &grid_json, const nlohmann::json& entities_json, Texture tex): grid(TileGrid::from_json(grid_json, tex)) {
    focus_entity = nullptr;
}
