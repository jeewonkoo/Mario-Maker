#ifndef VILLAIN_H
#define VILLAIN_H

#include<raylib.h>
#include<raymath.h>
#include "Level.h"

class Villain {
public:
    Villain();

    virtual void render(Vector2 top_left, Vector2 size);

    virtual void update(const Level& level, bool left, bool right, bool up, bool down);

    Rectangle rect() const { return {position.x, position.y, 1.0, 1.0};}

private:
    Texture tex;
    Vector2 position;
    Vector2 velocity;
};




#endif //VILLAIN_H