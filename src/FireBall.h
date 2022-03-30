#pragma once

#include "../Entity.h"

class FireBall : public Entity {
public:

    FireBall(float px, float py, Texture texture, bool facing_right);

    [[nodiscard]] Rectangle rect() const override;
    void on_collide(EntityCollision collision) override;
    void render(Vector2 top_left, Vector2 size) override;
    void update(const TileGrid& level, const InputState& keyboard_input) override;
    bool should_remove() override;
    EntityType type() override { return EntityType::FireBall; }
private:
    Texture tex;
    Vector2 position;
    Vector2 velocity;
    bool is_dead;
    bool facing_right;
};