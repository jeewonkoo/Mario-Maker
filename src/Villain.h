#ifndef VILLAIN_H
#define VILLAIN_H

#include<raylib.h>
#include<raymath.h>
#include "Level.h"

class Villain {
public:
    Villain();

    void render(Vector2 top_left, Vector2 size);

    void update(const Level& level, bool left, bool right, bool up, bool down);

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 mario_size = { 64, 64 };
    bool grounded{};
};



#endif //MARIO_MAKER_LEVEL_H