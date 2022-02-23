
#include "Mario.h"
#include <raymath.h>

Mario::Mario(double px, double py) {
	positionx = px;
	positiony = py;
}

void Mario::render(Vector2 top_left, Vector2 size) {
	DrawRectangleV(Vector2Add(top_left, {(float)positionx * 64, (float)positiony * 64}), mario_size, GREEN);

}


void Mario::update(bool left, bool right, bool up, bool down) {
	if (left && right) {
		dx += 0;
	}
	else if (right) {
		dx += 0.1;
	}
	else if (left) {
		dx -= 0.1;
	}

	if (up && positiony == 15) {
	    dy -= 2;
	} else if (down) {
		dy += 0.1;
	}

	dy += 0.1;


	positionx += dx;
	positiony += dy;

	if(positiony > 15){
	    positiony = 15;
	    dy = 0;
	}

	dx *= 0.5;
	dy *= 0.5;
}
