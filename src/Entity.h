#ifndef MARIO_MAKER_ENTITY_H
#define MARIO_MAKER_ENTITY_H

#include"Tile.h"
#include"Level.h"

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
    virtual void update(const Level& level) = 0;
};

#endif //MARIO_MAKER_ENTITY_H
