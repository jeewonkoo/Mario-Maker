
#include "Villain.h"
#include <raymath.h>
#include <raylib.h>
#include <algorithm>

Villain::Villain(float px, float py, Texture texture): position({px, py}), velocity({0,0}), Texture(texture){}

void Villain::render(Vector2 top_left, Vector2 size) {
    //DrawTexturePro(tex, Rectangle{ 187, 3, 16, 16 }, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}

void Villain::update(const Level& level, bool left, bool right, bool up, bool down) {
    if (left && right)  velocity.x += 0;

    else if (left)  velocity.x -=0.05; 

    else if (right) velocity.x += 0.05;

    else if (up) velocity.y -= 0.05;

    else if (down) velocity.x += 0.05;

    position = Vector2Add(position, velocity);


}