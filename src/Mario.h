#ifndef MARIO_H
#define MARIO_H

#include"Entity.h"
#include "InputState.h"

class Mario : public Entity {
public:
    Mario(float px, float py, Texture texture);

    void render(Vector2 top_left, Vector2 size) override;

    void update(const TileGrid &level, const InputState &keyboard_input) override;

    Rectangle rect() const override { return {position.x + 0.05f, position.y + 0.1f, 0.9, 0.9};}

    void on_collide(EntityCollision collision) override;

    bool should_remove() override;

    EntityType type() override { return EntityType::Mario; }

    ~Mario() override = default;
private:
    Vector2 position;
    Vector2 velocity;
    Texture tex;
    //whether mario is currently grounded
    bool grounded{};
    bool jumping{};
    //whether mario pressed space in the previous frame
    bool last_space{};

    float is_big;

    int frames_since_jump{};
    static constexpr float jump_instant_accel = 0.3;
    static constexpr float jump_continuous_accel = 0.025;
    static constexpr float low_speed_threshold = 0.2;
    static constexpr int jump_continuous_frames = 12;
    static constexpr int jump_continuous_delay = 4;
    static constexpr float gravity = 0.02;
    static constexpr float ground_acceleration_low_speed = 0.06;
    static constexpr float ground_acceleration_high_speed = 0.055;
    static constexpr float air_acceleration = 0.006;
    static constexpr float max_speed = 0.2;
    static constexpr float max_fall = 0.5;
    static constexpr float ground_traction = 0.05;
    static constexpr float air_traction = 0;
};

#endif
