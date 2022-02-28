#ifndef VILLAIN_H
#define VILLAIN_H

#include<raylib.h>
#include<raymath.h>
#include "Level.h"

class Villain {
public:
    Villain(float px, float py, Texture texture);

    virtual void render(Vector2 top_left, Vector2 size);

    virtual void update(const Level& level);

    Rectangle rect() const { return {position.x, position.y, 1.0, 1.0};}

private:
    Texture tex;
    Vector2 position;
    Vector2 velocity;

    Vector2 initialPosition;
};




#endif //VILLAIN_H