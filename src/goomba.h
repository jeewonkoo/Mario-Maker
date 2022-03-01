
#ifndef MARIO_MAKER_GOOMBA_H
#define MARIO_MAKER_GOOMBA_H

#include "Villain.h"

class Goomba : public Villain {
public:

    Goomba();

    void render(Vector2 top_left, Vector2 size, float a, float b, float c, float d);

    void update(const Level& level);

private:
    
};