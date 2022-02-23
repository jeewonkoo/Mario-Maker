
#ifndef MARIO_H
#define MARIO_H

class Mario {
public:
	Mario() {};
	void render();
	void update(bool left, bool right, bool up, bool down);
};