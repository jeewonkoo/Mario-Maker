//
// Created by 16182 on 3/30/2022.
//

#include "EntitySpawn.h"
#include "enemies/Boo.h"
#include "enemies/Goomba.h"
#include "enemies/Piranha.h"
#include "powerups/FireFlower.h"
#include "powerups/Mushroom.h"
#include "powerups/SmallShroom.h"
#include "powerups/TanookieLeaf.h"
#include "FireBall.h"
#include "Mario.h"
#include <memory>

std::unique_ptr<Entity> EntitySpawn::make(Texture tex, Mario* mario) {
    switch(type){
        case Type::Mario:
            return std::make_unique<Mario>(x, y, tex);
        case Type::Boo:
            return std::make_unique<Boo>(x, y, tex, mario);
        case Type::Goomba:
            return std::make_unique<Goomba>(x, y, tex);
        case Type::Piranha:
            return std::make_unique<Piranha>(x, y, tex);
        case Type::FireFlower:
            return std::make_unique<FireFlower>(x, y, tex);
        case Type::Mushroom:
            return std::make_unique<Mushroom>(x, y, tex);
        case Type::SmallShroom:
            return std::make_unique<SmallShroom>(x, y, tex);
        case Type::TanookieLeaf:
            return std::make_unique<TanookieLeaf>(x, y, tex);
        case Type::FireBall:
            return std::make_unique<FireBall>(x, y, tex, mario->is_right());
        default:
            throw std::runtime_error("unhandeled entity type id");
    }
}

nlohmann::json EntitySpawn::to_json() {
    nlohmann::json json;
    json["x"] = x;
    json["y"] = y;
    json["type"] = type;
    return json;
}

EntitySpawn EntitySpawn::from_json(const nlohmann::json &json) {
    return {json["x"], json["y"], json["type"]};
}
