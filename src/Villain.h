#ifndef VILLAIN_H
#define VILLAIN_H

#include<raylib.h>
#include<raymath.h>
#include "Level.h"

class Villain {
public:
    Villain();

    void render(Vector2 top_left, Vector2 size);

    virtual void update(const Level& level, bool left, bool right, bool up, bool down);

    Rectangle rect() const { return {position.x, position.y, 1.0, 1.0};}

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 mario_size = { 64, 64 };
    bool grounded{};
};


#endif //VILLAIN_H