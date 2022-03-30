#include "FireBall.h"
#include "../SpriteLocations.h"
#include <raymath.h>
#include <iostream>

/**
 * Constructor for Mushroom class. Sets private variable of FireFlower class with given parameters.
 *
 * @param px start x axis location
 * @param py start y axis location
 * @param texture rendered FireFlower image sprite
 */
FireBall::FireBall(float px, float py, Texture texture, bool facing_right) : tex(texture), position({ px, py }), velocity({ 0,0 }), is_dead(false), facing_right(facing_right) {
}

/**
 * Renders(draw) FireFlower on graphic. Accepts two Vector2 as parameters
 *
 * @param top_left top left location of mario on graphic
 * @param size size of FireFlower on graphic
 */
void FireBall::render(Vector2 top_left, Vector2 size) {
    DrawTexturePro(tex, SpriteLocations::FireFlower, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}

/**
 * Updates location and direction of FireFlower entity
 *
 * @param level TileGrid object to determine collision
 * @param keyboard_input pressed keyboard by user
 */
void FireBall::update(const TileGrid& level, const InputState& keyboard_input) {
    if (facing_right) {
        position = Vector2Add(position, { 1, -1 });
    }
    else {
        position = Vector2Add(position, { -1, -1 });
    }
}

/**
 * Resize hitbox of FireFlower entity
 * (Hitbox refers padding of entity image that determins collision with other entity)
 *
 * @return resized hitbox
 */
Rectangle FireBall::rect() const {
    return { position.x, position.y, 0.9, 0.9 };
}

/**
 * Collides entity against FireFlower.
 * If Mario collides with FireFlower, FireFlower is disappeared and Mario gets powerup.
 *
 *  @param collision array of colided entity set
 */
void FireBall::on_collide(EntityCollision collision) {
    if (collision.other.type() == EntityType::Mario) {
        is_dead = true;
    }
}

/**
 * Determines if FireFlower should be disappeared or not
 *
 * @return is_dead boolean private member variable
 */
bool FireBall::should_remove() {
    return is_dead;
}
