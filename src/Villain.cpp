
#include "Villain.h"
#include <raymath.h>
#include <raylib.h>
#include <algorithm>

Villain::Villain(float px, float py): position({px, py}), velocity({0,0}){}

void Villain::render(Vector2 top_left, Vector2 size) {
      
}

void Villain::update(const Level& level, bool left, bool right, bool up, bool down) {
    if (left && right)  velocity.x += 0;

    else if (left)  velocity.x -=0.05; 

    else if (right) velocity.x += 0.05;

    else if (up) velocity.y -= 0.05;

    else if (down) velocity.x += 0.05;

}

