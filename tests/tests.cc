#include "catch.hpp"
#include <raylib.h>
#include <raymath.h>
#include <memory>
#include <iostream>
#include "../src/TileGrid.h"
#include "../src/Mario.h"
#include "../src/enemies/Goomba.h"
#include "../src/enemies/Boo.h"
#include "../src/powerups/Mushroom.h"
#include "../src/powerups/SmallShroom.h"
#include "../src/Level.h"
#include "../src/SpriteLocations.h"



TEST_CASE("Test Collision,[Collision]") {
	SECTION("Not Colliding") {
		Rectangle rect1{5, 5, 5,5};
		Rectangle rect2{10, 10, 5, 5};
		REQUIRE_FALSE(collide_rect(rect1, rect2).has_value());
	}

	SECTION("Colliding left") {
		Rectangle rect1{5, 5, 5, 5};
		Rectangle rect2{4, 5, 5, 5};
		auto c = collide_rect(rect1, rect2);
		REQUIRE(collide_rect(rect1, rect2).has_value());
		REQUIRE(c->collision_side == Side::LEFT);
	}

	SECTION("Colliding right") {
		Rectangle rect1{5, 5, 5, 5};
		Rectangle rect2{6, 5, 5, 5};
		auto c = collide_rect(rect1, rect2);
		REQUIRE(collide_rect(rect1, rect2).has_value());
		REQUIRE(c->collision_side == Side::RIGHT);
	}

	SECTION("Colliding up") {
		Rectangle rect1{5, 5, 5, 5};
		Rectangle rect2{5, 4, 5, 5};
		auto c = collide_rect(rect1, rect2);
		REQUIRE(collide_rect(rect1, rect2).has_value());
		REQUIRE(c->collision_side == Side::TOP);
	}

	SECTION("Colliding down") {
		Rectangle rect1{5, 5, 5, 5};
		Rectangle rect2{5, 6, 5, 5};
		auto c = collide_rect(rect1, rect2);
		REQUIRE(collide_rect(rect1, rect2).has_value());
		REQUIRE(c->collision_side == Side::BOTTOM);
	}
}

TEST_CASE("Movement") {

	Level level{ Texture{},Texture{},5,5 };
	Mario& mario = level.mario();
	SECTION("Move Right") {
		Vector2 initialpos = mario.getPosition();
		InputState s = { false,true,false,false,false };
		level.update(s);

		Vector2 nextpos = mario.getPosition();

		REQUIRE(nextpos.x > initialpos.x);
	}

	SECTION("Move Right") {
		Vector2 initialpos = mario.getPosition();
		InputState s = { false,true,false,false,false };
		level.update(s);

		Vector2 nextpos = mario.getPosition();

		REQUIRE(nextpos.x > initialpos.x);
	}

	SECTION("Move Left") {
		Vector2 initialpos = mario.getPosition();
		InputState s = { true,false,false,false,false };
		level.update(s);

		Vector2 nextpos = mario.getPosition();

		REQUIRE(nextpos.x < initialpos.x);
	}
	
	SECTION("Jumping,[going up]") {

		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		Vector2 initialpos = mario.getPosition();
		InputState s1 = { false,false,false,false,true };
		level.update(s1);

		Vector2 nextpos = mario.getPosition();

		REQUIRE(nextpos.y < initialpos.y);
	}

	SECTION("Jumping,[going down]") {

		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		Vector2 initialpos = mario.getPosition();
		InputState s1 = { false,false,false,false,true };
		level.update(s1);

		InputState s2 = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s2);
		}

		Vector2 nextpos = mario.getPosition();

		REQUIRE(nextpos.y == initialpos.y);
	}

}

TEST_CASE("Goomba") {
	Level level{ Texture{},Texture{},5,8 };

	Tile t(true, TileLocations::Ground);
	
	for (int i = 0; i < 30; i++) {
		level.set_tile(i, 10,t);
	}


	SECTION("Goomba moving right") {

		EntitySpawn goomba(5, 10, EntitySpawn::Type::Goomba);
		level.add_entity(goomba, Texture{});

		Vector2 initialpos = goomba->get_position();


		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 5; i++) {
			level.update(s);
		}

		Vector2 finalPos = goomba->get_position();

		REQUIRE(finalPos.x > initialpos.x);
	}

	SECTION("Goomba moving left after hitting block") {
		auto g = std::make_unique<Goomba>(5, 10, Texture{});
		Goomba* goomba = g.get();
		level.add_entity(std::move(g));

		level.set_tile(8, 15, t);

		Rectangle rect1{ 8, 10.1, 5, 5 };
		Vector2 initialpos = goomba->get_position();


		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		Vector2 finalPos = goomba->get_position();

		REQUIRE(finalPos.x < initialpos.x);


	}

	SECTION("Mario kills Goomba while stepping on top") {

		level.set_tile(5, 12, t);
		auto g = std::make_unique<Goomba>(5, 10, Texture{});
		Goomba* goomba = g.get();
		level.add_entity(std::move(g));

		auto m = std::make_unique<Mario>(5, 8, Texture{});
		Mario* mario = m.get();
		level.add_entity(std::move(m));
		

		bool goomdead = goomba->is_goomba_dead();
		REQUIRE(goomdead == false);

		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		goomdead = goomba->is_goomba_dead();
		REQUIRE(goomdead);
	}

}

