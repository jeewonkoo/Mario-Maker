#include <raylib.h>
#include "Mario.h"
#include <raymath.h>
#include <algorithm>

Mario::Mario(float px, float py, Texture texture): position({px, py}), velocity({0,0}), tex(texture){}

void Mario::render(Vector2 top_left, Vector2 size) {
	DrawTexturePro(tex, Rectangle{ 187, 3, 16, 16 }, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}

void Mario::update(const Level &level, bool left, bool right, bool up, bool down, bool space) {
    float acceleration = grounded ? ground_acceleration : air_acceleration;
    float traction = grounded ? ground_traction : air_traction;
	if (left && right) {
		velocity.x += 0;
	}
	else if (right) {
		velocity.x += acceleration;
	}
	else if (left) {
		velocity.x -= acceleration;
	}

	if (space && grounded && (last_space != space)) {
	    frames_since_jump = 0;
	    velocity.y -= jump_instant_accel;
	}

	if (space && (frames_since_jump < jump_continuous_frames)){
	    velocity.y -= jump_continuous_accel;
	}

	velocity.y += gravity;


	position = Vector2Add(position, velocity);

	grounded = false;
	while(true){
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


	velocity.x = std::clamp(velocity.x, -max_speed, max_speed);

	if(velocity.y > max_fall){
	    velocity.y = max_fall;
	}

	if(velocity.x > 0){
	    velocity.x = std::max(velocity.x - traction, 0.f);
	} else {
	    velocity.x = std::min(velocity.x + traction, 0.f);
	}

	last_space = space;
	frames_since_jump++;
}
