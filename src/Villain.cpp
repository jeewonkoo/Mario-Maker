
#include "Villain.h"
#include <raymath.h>
#include <raylib.h>
#include <algorithm>

Villain::Villain(float px, float py, Texture texture) : position({ px, py }), velocity({ 0,0 }), tex(texture), initialPosition({ px,py }) {}

void Villain::render(Vector2 top_left, Vector2 size) {
    DrawTexturePro(tex, Rectangle{ 0, 0, 24, 25 }, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}

void Villain::update(const Level& level) {
    bool move_right = true;
    if (move_right) {
        position.x += 0.05;
        if (position.x == 64) move_right = false;
    
    }

    if (!move_right) {
        position.x -= 0.05;
        if (position.x == 0) move_right = true;
    }
}




