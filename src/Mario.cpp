
#include "Mario.h"
#include <raymath.h>

Mario::Mario(double px, double py) {
	positionx = px;
	positiony = py;
}

void Mario::render(Vector2 top_left, Vector2 size) {
	DrawRectangleV(Vector2Add(top_left, {(float)positionx, (float)positiony}), size, GREEN);

}


void Mario::update(bool left, bool right, bool up, bool down) {
	if (left == true && right == true) {
		positionx += 0;
	}
	else if (right == true) {
		positionx += 5;
	}
	else if (left == true) {
		positionx -= 5;
	}
	else if (up == true) {
		positiony -= 5;
	}
	else if (down == true) {
		positiony += 5;
	}
}
