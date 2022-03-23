#include "Piranha.h"
#include "../SpriteLocations.h"
#include<raymath.h>

Piranha::Piranha(float px, float py, Texture texture, Mario* mpt) : position({ px, py }), initPos({ px, py }), tex(texture), dormantPlant(0), activePlant(0), is_dead(false) {}

/**
 * Renders(draw) Piranha on graphic. Accepts two Vector2 as parameters
 * 
 * @param top_left top left location of mario on graphic 
 * @param size size of Piranha on graphic 
 */
void Piranha::render(Vector2 top_left, Vector2 size) {
	DrawTexturePro(tex, SpriteLocations::Piranha, Rectangle{ 0, 0, 64, 64 }, Vector2Subtract(top_left, Vector2Multiply(position, { 64.f, 64.f })), 0, WHITE);
}

/**
 * Updates location and direction of Piranha entity
 * 
 * @param level TileGrid object to determine collision 
 * @param keyboard_input pressed keyboard by user
 */
void Piranha::update(const TileGrid& level, const InputState& keyboard_input) {
	if (dormantPlant == 0) { // plant is active
		activePlant++;
		position.y = initPos.y;
		if (activePlant == 120) { // once plant has been active for 2 sec, go to dormant
			activePlant = 0;
			dormantPlant++;
		}
	}
	else { // plant is dormant
		dormantPlant++;
		position.y = initPos.y + 64;
		if (dormantPlant == 180) {	// once plant has been dormant for 3 sec, go to active
			dormantPlant = 0;
			activePlant++;
		}
	}


	
}

bool Piranha::should_remove() {
	return is_dead;
}

Rectangle Piranha::rect() const {
	return { position.x, position.y, 0.9, 0.9 };
}

/**
 * Collides entity against Piranha. 
 * If Mario jumps on the top of Piranha, Mario gets smaller.
 * 
 *  @param collision array of colided entity set 
 */
void Piranha::on_collide(EntityCollision collision) {
	return;
}