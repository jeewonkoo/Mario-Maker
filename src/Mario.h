
#ifndef MARIO_H
#define MARIO_H

#include<raylib.h>
#include<raymath.h>

class Mario {
public:
	Mario(double px, double py);

	void render(Vector2 top_left, Vector2 size);



	void update(bool left, bool right, bool up, bool down);
private:
	double positionx;
	double positiony;
};

#endif 
