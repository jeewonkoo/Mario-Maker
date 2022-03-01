#ifndef MARIO_MAKER_VILLAIN_H
#define MARIO_MAKER_VILLAIN_H

#include<raylib.h>
#include<raymath.h>
#include "Level.h"

class Villain {
public:
    Villain();
    Villain(float px, float py, Texture texture);

    virtual void render(Vector2 top_left, Vector2 size) =0;

    virtual void update(const Level& level) = 0;

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