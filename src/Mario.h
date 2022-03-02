#ifndef MARIO_H
#define MARIO_H

#include"Entity.h"

class Mario : public Entity {
public:
    Mario(float px, float py, Texture texture);

    void render(Vector2 top_left, Vector2 size) override;

    void update(const Level &level, bool left, bool right, bool up, bool down, bool space);

    void update(const Level &level) override{};

    Rectangle rect() const override { return {position.x, position.y, 0.9, 0.9};}

    void OnCollide(EntityCollision collision) override;
private:
    Vector2 position;
    Vector2 velocity;
    Vector2 mario_size = {64, 64};
    Texture tex;
    //whether mario is currently grounded
    bool grounded{};
    bool jumping{};
    //whether mario pressed space in the previous frame
    bool last_space{};

    int frames_since_jump{};
    static constexpr float jump_instant_accel = 0.25;
    static constexpr float jump_continuous_accel = 0.030;
    static constexpr int jump_continuous_frames = 8;
    static constexpr float gravity = 0.02;
    static constexpr float ground_acceleration = 0.055;
    static constexpr float air_acceleration = 0.005;
    static constexpr float max_speed = 0.3;
    static constexpr float max_fall = 0.5;
    static constexpr float ground_traction = 0.05;
    static constexpr float air_traction = 0;
};

#endif
