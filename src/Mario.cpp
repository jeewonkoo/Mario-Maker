#include <raylib.h>
#include "Mario.h"
#include <raymath.h>
#include <algorithm>

Mario::Mario(float px, float py): position({px, py}), velocity({0,0}){}

void Mario::render(Vector2 top_left, Vector2 size) {
	//DrawRectangleV(Vector2Add(top_left, Vector2Multiply(position, {64.f, 64.f})), mario_size, GREEN);

	Image mario_img = LoadImage("images/marios.png");
	Texture2D mario_texture = LoadTextureFromImage(mario_img);
	UnloadImage(mario_img);

	DrawTextureV(mario_texture, Vector2Add(top_left, Vector2Multiply(position, { 64.f, 64.f })), WHITE);
}

void Mario::update(const Level &level, bool left, bool right, bool up, bool down, bool space) {
	if (left && right) {
		velocity.x += 0;
	}
	else if (right) {
		velocity.x += 0.05;
	}
	else if (left) {
		velocity.x -= 0.05;
	}

	if (space && grounded && (last_space != space)) {
	    velocity.y -= 0.45;
	} else if (down) {
		velocity.y += 0.05;
	}

	velocity.y += 0.02;


	position = Vector2Add(position, velocity);

	grounded = false;
	while(true){
	    auto collisions = level.collide(rect());

        if(collisions.eject_vector.has_value()){
            auto eject = collisions.eject_vector.value();
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

	velocity = Vector2Multiply(velocity, {0.9f, 0.9f});
	last_space = space;
}
