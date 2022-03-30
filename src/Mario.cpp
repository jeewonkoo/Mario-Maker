#include "Mario.h"
#include <raylib.h>
#include <raymath.h>

/**
 * Constructor for mario class. Sets private variable of mario class with given parameters. 
 * 
 * @param px start x axis location
 * @param py start y axis location
 * @param texture rendered mario image sprite
 */
Mario::Mario(float px, float py, Texture texture): position({px, py}), velocity({0,0}), tex(texture), dead(false), invincibility(0) {
    for(int i = 0; i < sprite_sources.size(); i++){
        sprite_dests[i] = {0, 0, sprite_sources[i].width * 3, sprite_sources[i].height*3};
        hit_boxes[i] = {0, 0, sprite_sources[i].width * 3.f / 64.f, sprite_sources[i].height * 3.f / 64.f};
    }
}

/**
 * Renders(draw) mario on graphic. Accepts two Vector2 as parameters
 * 
 * @param top_left top left location of mario on graphic 
 * @param size size of mario on graphic 
 */
void Mario::render(Vector2 top_left, Vector2 size) {
    DrawTexturePro(tex, sprite_sources.at((size_t)power_up), sprite_dests.at((size_t)power_up), Vector2Subtract(top_left, Vector2Multiply(position, {64.f, 64.f })), 0, WHITE);
}

/**
 * Updates location and direction of mario entity
 * 
 * @param level TileGrid object to determine collision 
 * @param keyboard_input pressed keyboard by user to determine directions/jump of mario entity 
 */
void Mario::update(const TileGrid &level, const InputState & keyboard_input) {

    if (power_up == MarioPowerUp::SmallInv)
        invincibility++;
    if (invincibility == 180) {
        invincibility = 0;
        power_up = MarioPowerUp::Small;
    }

    float acceleration = [&]{
       if(grounded){
           if(std::abs(velocity.x) < low_speed_threshold){
               return ground_acceleration_low_speed;
           } else {
               return ground_acceleration_high_speed;
           }
       } else {
           return air_acceleration;
       }
    }();

    float traction = grounded ? ground_traction : air_traction;
	if (keyboard_input.left && keyboard_input.right) {
		velocity.x += 0;
	}
	else if (keyboard_input.right) {
		velocity.x += acceleration;
        facing_right = true;
	}
	else if (keyboard_input.left) {
		velocity.x -= acceleration;
        facing_right = false;
	}

	if (keyboard_input.space && grounded && (last_space != keyboard_input.space)) {
	    frames_since_jump = 0;
	    velocity.y -= jump_instant_accel;
	}

	if (keyboard_input.space
	    && (frames_since_jump < jump_continuous_frames)
	    && (frames_since_jump >= jump_continuous_delay)){
	    velocity.y -= jump_continuous_accel;
	}

	velocity.y += gravity;

	if(velocity.x > 0){
	    velocity.x = std::max(velocity.x - traction, 0.f);
	} else {
	    velocity.x = std::min(velocity.x + traction, 0.f);
	}


	velocity.x = std::clamp(velocity.x, -max_speed, max_speed);

	if(velocity.y > max_fall){
	    velocity.y = max_fall;
	}


	position = Vector2Add(position, velocity);

	grounded = false;
	//terminate the loop if too many collisions
	for(int coll_idx = 0; coll_idx < 10; coll_idx++) {
	    auto collisions = level.collide(rect());

        if(collisions.eject_vector.has_value()){

            auto eject = collisions.eject_vector.value();

            //ignore collisions that are impossible because of our movement direction
            if(Vector2DotProduct(eject, velocity) > 0) break;
            position = Vector2Add(position, eject);
            auto eject_norm = Vector2Normalize(eject);
            auto velocity_diff = Vector2DotProduct(velocity, eject_norm);
            velocity = Vector2Subtract(velocity, Vector2Multiply(eject_norm, {velocity_diff, velocity_diff}));

            if(std::find_if(collisions.collisions.begin(), collisions.collisions.end(), [](auto&a){return a.collision.collision_side == Side::BOTTOM;}) != collisions.collisions.end()){
                grounded = true;
            }
        } else {
            break;
        }
    }


	last_space = keyboard_input.space;
	frames_since_jump++;
}

/**
 * Collides entity against the mario. Determines if tile collides with other entity.
 * 
 *  @param collision array of colided entity set 
 */
void Mario::on_collide(EntityCollision collision) {
    switch(collision.other.type()){
        case EntityType::Mushroom:
            power_up = MarioPowerUp::Big;
            break;
        case EntityType::SmallShroom:
            power_up = MarioPowerUp::Small;
            break;
        case EntityType::FireFlower:
            power_up = MarioPowerUp::Fire;
            break;
        case EntityType::JumpEnemy:
            if(collision.side == Side::BOTTOM && velocity.y >= 0){
                velocity.y = -jump_instant_accel;
                frames_since_jump = 0;
            }
            if (collision.side != Side::BOTTOM){
                if (power_up == MarioPowerUp::Small) {
                    dead = true;
                } else {
                    power_up = MarioPowerUp::SmallInv;
                }
            }

            break;
        case EntityType::SpikeEnemy:
            if (power_up == MarioPowerUp::Small) {
                dead = true;
                return;
            }
            if (collision.side != Side::BOTTOM)
                power_up = MarioPowerUp::SmallInv;
            break;
        default:
            break;
    }
}

/**
 * Resize hitbox of Mario entity
 * (Hitbox refers padding of entity image that determins collision with other entity)
 * 
 * @return box resized hitbox 
 */
Rectangle Mario::rect() const {
    auto box = hit_boxes.at((size_t)power_up);
    box.x += position.x;
    box.y += position.y;
    return box;
}

/**
 * Determines if mario entity should be removed or not 
 * 
 * @return false 
 */
bool Mario::should_remove() {
    return false;
}

bool Mario::is_dead() {
    return dead;
}

bool Mario::is_right() {
    return facing_right;
}
