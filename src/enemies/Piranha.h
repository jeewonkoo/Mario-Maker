#pragma once

#include "../Entity.h"
#include "../Mario.h"

class Piranha : public Entity {
public:
	Piranha(float px, float py, Texture texture, Mario* mpt);

	[[nodiscard]] Rectangle rect() const override;
	void on_collide(EntityCollision collision) override;
	void render(Vector2 top_left, Vector2 size) override;
	void update(const TileGrid& level, const InputState& keyboard_input) override;
	EntityType type() override { return EntityType::SpikeEnemy; }

private:
	Texture tex;
	Vector2 initPos;
	Vector2 position;
	int dormantPlant; // keep track of how long the plant is dormant
	int activePlant; // keep track of how long the plant is active
};