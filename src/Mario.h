#ifndef MARIO_H
#define MARIO_H

#include <array>
#include "Entity.h"
#include "InputState.h"

enum class MarioPowerUp {
    None,
    Big,
    Small,
    Fire
};

class Mario : public Entity {
public:
    Mario(float px, float py, Texture texture);

    void render(Vector2 top_left, Vector2 size) override;

    void update(const TileGrid &level, const InputState &keyboard_input) override;

    Rectangle rect() const override;

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

    MarioPowerUp power_up = MarioPowerUp::None;

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

    static constexpr std::array<Rectangle, 4> sprite_sources = {
            Rectangle{ 187, 3, 16, 16 },
            Rectangle{ 186, 25, 20, 27 },
            Rectangle{ 187, 3, 16, 16 },
            Rectangle{ 186, 87, 19, 27 },
    };

    static constexpr std::array<Rectangle, 4> hit_boxes = {
            Rectangle{ 0, 0, 16*3, 16*3 },
            Rectangle{ 0, 0, 20*3, 27*3 },
            Rectangle{ 0, 0, 32, 32 },
            Rectangle{ 0, 0, 19*3, 27*3 },
    };
};

#endif
