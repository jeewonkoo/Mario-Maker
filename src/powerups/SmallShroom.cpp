#include "SmallShroom.h"
#include<raymath.h>


SmallShroom::SmallShroom(float px, float py, Texture texture) : tex(texture), position({ px, py }), velocity({ 0.13,0 }), is_dead(false) {
}

void SmallShroom::render(Vector2 top_left, Vector2 size) {
    top_left = Vector2Subtract(top_left, { 32.f, 32.f });
    DrawTexturePro(tex, Rectangle{ 0, 0, 24, 25 }, Rectangle{ 0, 0, 32, 32 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}
#include<iostream>
void SmallShroom::update(const TileGrid& level, const InputState& keyboard_input) {

    position = Vector2Add(position, velocity);
    velocity.y += 0.02;

    //terminate the loop if too many collisions
    for (int coll_idx = 0; coll_idx < 10; coll_idx++) {
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
            else if (std::find_if(collisions.collisions.begin(), collisions.collisions.end(), [](auto& a) {return a.collision.collision_side == Side::LEFT; }) != collisions.collisions.end()) {
                velocity.x = 0.05;
            }
        }
        else {
            break;
        }
    }
}

Rectangle SmallShroom::rect() const {
    return { position.x, position.y, 0.9, 0.9 };
}

void SmallShroom::on_collide(EntityCollision collision) {
    if (collision.side == Side::TOP) {
        is_dead = true;
    }
}

bool SmallShroom::should_remove() {
    return is_dead;
}
