//
// Created by 16182 on 2/23/2022.
//

#ifndef MARIO_MAKER_LEVEL_H
#define MARIO_MAKER_LEVEL_H

#include<array>
#include<raylib.h>

class Level {
public:
    Level(){};
    void render(Vector2 top_left, Vector2 bottom_right);
    std::array<std::array<bool, 16>, 16> tiles{};
};


#endif //MARIO_MAKER_LEVEL_H
