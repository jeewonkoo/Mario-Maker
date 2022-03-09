#include "Boo.h"
#include "../SpriteLocations.h"
#include<raymath.h>

Boo::Boo(float px, float py, Texture texture, Mario* mpt) : position({ px, py }), velocity({ 0,0 }), tex(texture), MarioPointer(mpt),is_dead(false) {}

void Boo::render(Vector2 top_left, Vector2 size) {
	DrawTexturePro(tex, SpriteLocations::BooOpen, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}

void Boo::update(const TileGrid& level, const InputState& keyboard_input) {
	Vector2 mPos = MarioPointer->getPosition();
	if (mPos.x < this->position.x) {
		position.x -= 0.03;
	}
	else if (mPos.x > this->position.x) {
		position.x += 0.03;
	}

	if (mPos.y > this->position.y) {
		position.y += 0.03;
	}
	else if (mPos.y < this->position.y) {
		position.y -= 0.03;
	}
	
}

Rectangle Boo::rect() const {
	return { position.x, position.y, 0.9, 0.9 };
}

void Boo::on_collide(EntityCollision collision) {
	return;
}

bool Boo::should_remove() {
	return is_dead;
}