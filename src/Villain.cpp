
#include "Villain.h"
#include <raymath.h>
#include <raylib.h>
#include <algorithm>

Villain::Villain(float px, float py, Texture texture): position({px, py}), velocity({0,0}), Texture(texture){}, initialPosition({px,py})

void Villain::render(Vector2 top_left, Vector2 size) {
    DrawTexturePro(tex, Rectangle{ 187, 3, 16, 16 }, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}

void Villain::update(const Level& level) {
    if (position.x <= initialPosition.x + 10) {
        position.x += 1;
    }
    else {
        position.x -= 1;
    }
}


