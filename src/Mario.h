
#ifndef MARIO_H
#define MARIO_H

class Mario {
public:
	Mario() {};
	void render(Vector2 top_left, Vector2 size);
	void update(bool left, bool right, bool up, bool down);
};