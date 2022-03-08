#include "Mushroom.h"
#include<raymath.h>

Mushroom::Mushroom (float px, float py, Texture texture) : position({ px, py }), velocity({ 0.05,0 }), tex(texture), is_dead(false) {
    is_big = rand() % 2 + 1;
}

void Mushroom::render(Vector2 top_left, Vector2 size) {
    top_left = Vector2Subtract(top_left, { (int)is_big % 2 * 32.f, (int)is_big % 2 * 32.f });
    DrawTexturePro(tex, Rectangle{ 0, 0, 24, 25 }, Rectangle{ 0, 0, is_big * 32, is_big * 32 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}
void Mushroom::update (const TileGrid& level, const InputState & keyboard_input) {

    position = Vector2Add(position, velocity);
    velocity.y += 0.02;

    while (true) {
        auto collisions = level.collide(rect());

        if (collisions.eject_vector.has_value()) {

            auto eject = collisions.eject_vector.value();

            //ignore collisions that are impossible because of our movement direction
            if (Vector2DotProduct(eject, velocity) > 0) break;
            position = Vector2Add(position, eject);
            auto eject_norm = Vector2Normalize(eject);
            auto velocity_diff = Vector2DotProduct(velocity, eject_norm);
            velocity = Vector2Subtract(velocity, Vector2Multiply(eject_norm, { velocity_diff, velocity_diff }));


            if (std::find_if(collisions.collisions.begin(), collisions.collisions.end(), [](auto& a) {return a.collision.collision_side == Side::RIGHT; }) != collisions.collisions.end()) {
                velocity.x = -0.05;
            }
            else if(std::find_if(collisions.collisions.begin(), collisions.collisions.end(), [](auto& a) {return a.collision.collision_side == Side::LEFT; }) != collisions.collisions.end()) {
                velocity.x = 0.05;
            }
        }
        else {
            break;
        }
    }
}

Rectangle Mushroom::rect() const {
    return {position.x, position.y, 0.9, 0.9};
}

void Mushroom::on_collide(EntityCollision collision) {
    if(collision.side == Side::TOP){
        is_dead = true;
    }
}

bool Mushroom::should_remove() {
    return is_dead;
}

int Mushroom::is_big() {
    return is_big;
}
