//
// Created by 16182 on 3/23/2022.
//

#ifndef MARIO_MAKER_BUILDERUI_H
#define MARIO_MAKER_BUILDERUI_H

#include<raylib.h>
#include<raymath.h>
#include "Level.h"
#include "SpriteLocations.h"
#include<memory>
#include "powerups/Mushroom.h"
class BuilderUI {
public:
    BuilderUI(Level & level, Texture sprite_tex, Texture tile_tex);
    void handle_events(); 
    void render(Vector2 top_left, Vector2 size);

private:
    enum ActionType {
        DELETE,
        TILE,
        MUSHROOM,
        SMALLSHROOM,
        FIREFLOWER,
        TANOOKIE,
        GOOMBA,
        BOO,
        PIRANHA,
        NONE
    };

    Level& level;
    Texture sprite_tex;
    Texture tile_tex;
    ActionType current_action = NONE;
    bool pressed_last_frame = false;

    static ActionType icon_at(int x, int y){
        if(y < 128){
            return TILE;
        }

        if(y < 256){
            return MUSHROOM;
        }

        if (y < 384) {
            return SMALLSHROOM;
        }

        if (y < 512) {
            return FIREFLOWER;
        }

        if (y < 640) {
            return TANOOKIE;
        }

        if (y < 768) {
            return GOOMBA;
        }

        if (y < 896) {
            return BOO;
        }

        if (y < 1024) {
            return PIRANHA;
        }

        if(y < 1152){
            return DELETE;
        }

        

        return NONE;
    }
};


#endif //MARIO_MAKER_BUILDERUI_H
