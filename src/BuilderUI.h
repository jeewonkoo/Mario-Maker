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
    BuilderUI(Level & level, Texture sprite_tex, Texture tile_tex): level(level), sprite_tex(sprite_tex), tile_tex(tile_tex){}
    void handle_events(){
        bool pressed_this_frame = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        if(pressed_this_frame && !pressed_last_frame){
            if(GetMouseX() > 1024 - 128){
                current_action = icon_at(GetMouseX(), GetMouseY());
            } else {
                auto offset = level.get_camera_offset();
                float x = GetMouseX() / 64.f + offset.x - 8;
                float y = GetMouseY() / 64.f + offset.y;





                if(current_action == TILE){
                    level.set_tile(x, y, {.solid = true, .tex_src = TileLocations::Ground});
                } else if(current_action == MUSHROOM){
                    level.add_entity(std::make_unique<Mushroom>(x, y, sprite_tex));
                }
            }
        }

        pressed_last_frame = pressed_this_frame;
    }
    void render(Vector2 top_left, Vector2 size){
        DrawRectangle(1024 - 128, 0, 128, 1024, BLUE);
        DrawTexturePro(sprite_tex, SpriteLocations::Mushroom, {1024 - 128, 0, 128, 128}, {0,0}, 0, WHITE);
        DrawTexturePro(tile_tex, TileLocations::Ground, {1024 - 128, 128, 128, 128}, {0,0}, 0, WHITE);

    }

private:
    enum ActionType {
        DELETE,
        MUSHROOM,
        TILE,
        NONE
    };

    Level& level;
    Texture sprite_tex;
    Texture tile_tex;
    ActionType current_action;
    bool pressed_last_frame = false;

    static ActionType icon_at(int x, int y){
        if(y < 128){
            return MUSHROOM;
        }

        if(y < 256){
            return TILE;
        }

        if(y < 384){
            return DELETE;
        }

        return NONE;
    }
};


#endif //MARIO_MAKER_BUILDERUI_H
