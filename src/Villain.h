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
};


#endif //VILLAIN_H