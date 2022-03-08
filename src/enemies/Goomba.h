#ifndef MARIO_MAKER_GOOMBA_H
#define MARIO_MAKER_GOOMBA_H

#include "../Entity.h"

class Goomba : public Entity {
public:

    Goomba(float px, float py, Texture texture);

    [[nodiscard]] Rectangle rect() const override;
    void on_collide(EntityCollision collision) override;
    void render(Vector2 top_left, Vector2 size) override;
    void update(const TileGrid& level, const InputState & keyboard_input) override;
    bool should_remove() override;
    EntityType type() override { return EntityType::JumpEnemy; }
private:
    Texture tex;
    Vector2 position;
    Vector2 velocity;
    bool is_dead;
};

#endif