#ifndef MARIO_MAKER_GOOMBA_H
#define MARIO_MAKER_GOOMBA_H

#include "Entity.h"

class Goomba : public Entity {
public:

    Goomba(float px, float py, Texture texture);

    [[nodiscard]] Rectangle rect() const override;
    void OnCollide(EntityCollision collision) override;
    void render(Vector2 top_left, Vector2 size) override;
    void update(const Level& level) override;

private:
    Texture tex;
    Vector2 position;
    Vector2 velocity;

    Vector2 initialPosition;
};

#endif