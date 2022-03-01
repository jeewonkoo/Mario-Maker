#ifndef VILLAIN_H
#define VILLAIN_H

#include<raylib.h>
#include<raymath.h>
#include "Level.h"

class Villain {
public:
    Villain(float px, float py, Texture texture);

    virtual void render(Vector2 top_left, Vector2 size, float a, float b, float c, float d);

    virtual void update(const Level& level);

    Rectangle rect() const { return {position.x, position.y, 0.9, 0.9};}

private:
    Texture tex;
    Vector2 position;
    Vector2 velocity;

    Vector2 initialPosition;


    bool left;
    bool right;
};




#endif //VILLAIN_H