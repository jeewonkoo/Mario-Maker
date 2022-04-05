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
	SECTION("Goomba moving right") {
		Level level{ Texture{},Texture{},30,8 };

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		EntitySpawn g(5, 9, EntitySpawn::Type::Goomba);
		Goomba* goomba = (Goomba*)(level.add_entity(g, Texture{}));
		
		Vector2 initialpos = goomba->get_position();


		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 5; i++) {
			level.update(s);
		}

		Vector2 finalPos = goomba->get_position();

		REQUIRE(finalPos.x > initialpos.x);
	}

	SECTION("Goomba moving left after hitting block") {
		Level level{ Texture{},Texture{},30,8 };

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		EntitySpawn g(5, 10, EntitySpawn::Type::Goomba);
		Goomba* goomba = (Goomba*)(level.add_entity(g, Texture{}));

		level.set_tile(8, 9, t);

		Vector2 initialpos = goomba->get_position();


		InputState s = { true,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		Vector2 finalPos = goomba->get_position();

		REQUIRE(finalPos.x < initialpos.x);


	}

	SECTION("Mario kills Goomba while stepping on top") {
		Level level{ Texture{},Texture{},5,8 };

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		level.set_tile(5, 12, t);
		EntitySpawn g(5, 10, EntitySpawn::Type::Goomba);
		Goomba* goomba = (Goomba*)(level.add_entity(g, Texture{}));

		

		bool goomdead = goomba->is_goomba_dead();
		REQUIRE(goomdead == false);

		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		goomdead = goomba->is_goomba_dead();
		REQUIRE(goomdead);
	}

	SECTION("Goomba damages mario") {
		Level level{ Texture{},Texture{},10,8 };
		Mario& mario = level.mario();

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}


		EntitySpawn g(5, 10, EntitySpawn::Type::Goomba);
		Goomba* goomba = (Goomba*)(level.add_entity(g, Texture{}));



		MarioPowerUp currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::Big);

		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::SmallInv);
	}

}


TEST_CASE("BOO") {
	SECTION("Boo moves towards mario") {
		Level level{ Texture{},Texture{},30,8 };

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		EntitySpawn b(5, 0, EntitySpawn::Type::Boo);
		Boo* boo = (Boo*)(level.add_entity(b, Texture{}));

		Vector2 initialpos = boo->get_position();


		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		Vector2 finalpos = boo->get_position();

		REQUIRE(initialpos.x < finalpos.x);
		REQUIRE(initialpos.y < finalpos.y);
	}

	SECTION("Boo Damages Mario") {
		Level level{ Texture{},Texture{},10,8 };
		Mario& mario = level.mario();

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}


		EntitySpawn b(9, 5, EntitySpawn::Type::Boo);
		Boo* boo = (Boo*)(level.add_entity(b, Texture{}));



		MarioPowerUp currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::Big);

		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::SmallInv);
	}

}

TEST_CASE("Small Mushroom") {
	SECTION("Small Mushroom moving right") {
		Level level{ Texture{},Texture{},30,8 };

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		EntitySpawn g(5, 9, EntitySpawn::Type::SmallShroom);
		SmallShroom* smallshroom = (SmallShroom*)(level.add_entity(g, Texture{}));

		Vector2 initialpos = smallshroom->getPosition();


		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 5; i++) {
			level.update(s);
		}

		Vector2 finalPos = smallshroom->getPosition();

		REQUIRE(finalPos.x > initialpos.x);
	}

	SECTION("Small mushroom left after hitting block") {
		Level level{ Texture{},Texture{},30,8 };

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		EntitySpawn g(5, 10, EntitySpawn::Type::SmallShroom);
		SmallShroom* smallshroom = (SmallShroom*)(level.add_entity(g, Texture{}));

		level.set_tile(8, 9, t);

		Vector2 initialpos = smallshroom->getPosition();


		InputState s = { true,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		Vector2 finalPos = smallshroom->getPosition();

		REQUIRE(finalPos.x < initialpos.x);
	}

	SECTION("Mario gets Small after stepping on small mushroom") {
		Level level{ Texture{},Texture{},5,8 };
		Mario& mario = level.mario();
		

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		MarioPowerUp currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::Big);

		level.set_tile(8, 9, t);
		EntitySpawn g(5, 6, EntitySpawn::Type::SmallShroom);
		SmallShroom* smallshroom = (SmallShroom*)(level.add_entity(g, Texture{}));

		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::Small);

	}
}

TEST_CASE("Mushroom") {
	SECTION("Mushroom moving right") {
		Level level{ Texture{},Texture{},30,8 };

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		EntitySpawn g(5, 9, EntitySpawn::Type::Mushroom);
		Mushroom* mush = (Mushroom*)(level.add_entity(g, Texture{}));

		Vector2 initialpos = mush->getPosition();


		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 5; i++) {
			level.update(s);
		}

		Vector2 finalPos = mush->getPosition();

		REQUIRE(finalPos.x > initialpos.x);
	}

	SECTION("Small mushroom left after hitting block") {
		Level level{ Texture{},Texture{},30,8 };

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		EntitySpawn g(5, 10, EntitySpawn::Type::Mushroom);
		Mushroom* mush = (Mushroom*)(level.add_entity(g, Texture{}));

		level.set_tile(8, 9, t);

		Vector2 initialpos = mush->getPosition();


		InputState s = { true,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		Vector2 finalPos = mush->getPosition();

		REQUIRE(finalPos.x < initialpos.x);
	}

	SECTION("Mario gets big after stepping on mushroom") {
		Level level{ Texture{},Texture{},5,8 };
		Mario& mario = level.mario();


		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		level.set_tile(8, 9, t);

		MarioPowerUp currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::Big);

		EntitySpawn g(5, 6, EntitySpawn::Type::SmallShroom);
		SmallShroom* smallshroom = (SmallShroom*)(level.add_entity(g, Texture{}));

		InputState s = { false,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::Small);

		EntitySpawn g1(5, 6, EntitySpawn::Type::Mushroom);
		Mushroom* mush = (Mushroom*)(level.add_entity(g1, Texture{}));

		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::Big);

	}

}

TEST_CASE("FireFlower") {
	SECTION("Mario gets a FireFlower powerup walking on the fireflower") {
		Level level{ Texture{},Texture{},5,8 };
		Mario& mario = level.mario();

		Tile t(true, TileLocations::Ground);

		for (int i = 0; i < 30; i++) {
			level.set_tile(i, 10, t);
		}

		EntitySpawn g(10, 10, EntitySpawn::Type::FireFlower);
		Entity* fire = (Entity*)(level.add_entity(g, Texture{}));



		InputState s = { true,false,false,false,false };
		for (int i = 0; i < 100; i++) {
			level.update(s);
		}

		MarioPowerUp currmar = mario.get_PowerUp();
		REQUIRE(currmar == MarioPowerUp::Fire);
	}

}

