#ifndef MARIO_MAKER_GOOMBA_H
#define MARIO_MAKER_GOOMBA_H

#include "Villain.h"

class Goomba : public Villain {
public:

    Goomba(float px, float py, Texture texture);

    void render(Vector2 top_left, Vector2 size);

    void update(const Level& level);

private:
    Texture tex;
    Vector2 position;
    Vector2 velocity;

    Vector2 initialPosition;
};

#endif