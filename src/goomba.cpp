#include "goomba.h"

<<<<<<< HEAD
Goomba::Goomba (float px, float py, Texture texture) : position({ px, py }), velocity({ 0.05,0 }), tex(texture), initialPosition({ px,py }) {}
=======
<<<<<<< HEAD
Goomba::Goomba(float px, float py, Texture texture) : position({ px, py }), velocity({ 0.05,0 }), tex(texture), initialPosition({ px,py }) {}
=======
<<<<<<< HEAD
Goomba::Goomba () {}
=======
Goomba::Goomba (float px, float py, Texture texture) : position({ px, py }), velocity({ 0.05,0 }), tex(texture), initialPosition({ px,py }) {}
>>>>>>> 72c6ae19bd5e711f6a4bb8f57db8a01ebb07e4ea
>>>>>>> 46512bd1f63792afce54eddbd4346872773d0f8d
>>>>>>> d7d22458e830f101ca5cb891608bb7a04e2602fc

void Goomba::render(Vector2 top_left, Vector2 size) {
    DrawTexturePro(tex, Rectangle{ 0, 0, 24, 25 }, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}
void Goomba::update (const Level& level) {
     
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