//
// Created by 16182 on 3/30/2022.
//

#ifndef MARIO_MAKER_ENTITYSPAWN_H
#define MARIO_MAKER_ENTITYSPAWN_H


#include<memory>
#include<nlohmann/json.hpp>
#include <raylib.h>
#include "Mario.h"
#include "Entity.h"

struct EntitySpawn {
    enum class Type {
        Mario,
        Boo,
        Goomba,
        Piranha,
        FireFlower,
        Mushroom,
        SmallShroom,
        TanookieLeaf,
    };


    EntitySpawn(float x, float y, Type type): x(x), y(y), type(type){}

    Type type;
    float x, y;

    std::unique_ptr<Entity> make(Texture tex, Mario* mario);
    nlohmann::json to_json();
    static EntitySpawn from_json(const nlohmann::json & json);
};


#endif //MARIO_MAKER_ENTITYSPAWN_H
