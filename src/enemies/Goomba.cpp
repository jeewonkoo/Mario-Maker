#include "Goomba.h"
#include "../SpriteLocations.h"
#include<raymath.h>

Goomba::Goomba (float px, float py, Texture texture) : tex(texture), position({ px, py }), velocity({ 0.05,0 }), is_dead(false) {}

void Goomba::render(Vector2 top_left, Vector2 size) {
    DrawTexturePro(tex, SpriteLocations::GoombaStep1, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}
void Goomba::update (const TileGrid& level, const InputState & keyboard_input) {

    position = Vector2Add(position, velocity);
    velocity.y += 0.02;

    //terminate the loop if too many collisions
    for(int coll_idx = 0; coll_idx < 10; coll_idx++) {
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

Rectangle Goomba::rect() const {
    return {position.x, position.y, 0.9, 0.9};
}

void Goomba::on_collide(EntityCollision collision) {
    if(collision.other.type() == EntityType::Mario){
        if(collision.side == Side::TOP){
            is_dead = true;
        }
    }
}

bool Goomba::should_remove() {
    return is_dead;
}
