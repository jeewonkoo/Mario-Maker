
#include "Mario.h"
#include <raymath.h>

Mario::Mario(float px, float py): position({px, py}), velocity({0,0}){}

void Mario::render(Vector2 top_left, Vector2 size) {
	DrawRectangleV(Vector2Add(top_left, Vector2Multiply(position, {64.f, 64.f})), mario_size, GREEN);

}


void Mario::update(bool left, bool right, bool up, bool down) {
	if (left && right) {
		velocity.x += 0;
	}
	else if (right) {
		velocity.x += 0.1;
	}
	else if (left) {
		velocity.x -= 0.1;
	}

	if (up && position.y == 15) {
	    velocity.y -= 2;
	} else if (down) {
		velocity.y += 0.1;
	}

	velocity.y += 0.1;


	position = Vector2Add(position, velocity);

	if(position.y > 15){
	    position.y = 15;
	    velocity.y = 0;
	}

	velocity = Vector2Multiply(velocity, {0.2f, 0.2f});
}
