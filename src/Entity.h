#ifndef MARIO_MAKER_ENTITY_H
#define MARIO_MAKER_ENTITY_H

#include"Tile.h"
#include"TileGrid.h"
#include "InputState.h"

class Entity;

struct EntityCollision {
    Entity& other;
    Side side;
};

class Entity {
public:
    [[nodiscard]] virtual Rectangle rect() const = 0;
    virtual void OnCollide(EntityCollision collision) = 0;
    virtual void render(Vector2 top_left, Vector2 size) = 0;
    virtual void update(const TileGrid &level, const InputState &keyboard_input) = 0;
    virtual ~Entity() = default;
};

#endif //MARIO_MAKER_ENTITY_H
