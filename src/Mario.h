
#ifndef MARIO_H
#define MARIO_H

class Mario {
public:
	Mario() {};
	Mario(double px, double py);
	void render();
	void update(bool left, bool right, bool up, bool down);
private:
	double positionx;
	double positiony;
};