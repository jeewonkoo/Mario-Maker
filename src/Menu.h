//
// Created by 16182 on 4/5/2022.
//

#ifndef MARIO_MAKER_MENU_H
#define MARIO_MAKER_MENU_H
#include<raylib.h>
#include<vector>
#include<string>
#include<functional>
class Menu {
public:
    Menu(std::function<void(std::string)> load_level, std::function<void()> make_level): load_level(load_level), make_level(make_level){}
    void open(){
        if(current_mode == CLOSED){
            current_mode = TOP;
        }
    }
    void close(){
        current_mode = CLOSED;
    }
    void render(){
        switch(current_mode){
            case TOP:
                DrawRectangleRec(play_button_rect, GRAY);
                DrawText("play level", play_button_rect.x+50, play_button_rect.y+50, 50, BLACK);
                DrawRectangleRec(make_button_rect, GRAY);
                DrawText("make level", make_button_rect.x+50, make_button_rect.y+50, 50, BLACK);
                break;
            case CLOSED:
                break;
            case LOAD:
                for(auto& item : available_levels){
                    item.render();
                }
                break;
            case MAKE:
                break;
        }
    }

    void handle_events(){
        int mx = GetMouseX();
        int my = GetMouseY();
        switch(current_mode){
            case TOP:
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    if(in_rect(play_button_rect, mx, my)){
                        available_levels = make_load_menu();
                        current_mode = LOAD;
                    } else if(in_rect(make_button_rect, mx, my)){
                        make_level();
                    }
                }
                break;
            case CLOSED:
                break;
            case LOAD:
                for(auto& item : available_levels){
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && in_rect(item.rect, mx, my)){
                        item.on_click();
                    }
                }
                break;
            case MAKE:
                break;
        }

    }

private:
    struct MenuItem {
        Rectangle rect;
        std::function<void()> on_click;
        std::string name;

        void render(){
            DrawRectangleRec(rect, GRAY);
            DrawText(name.c_str(), rect.x+10, rect.y+10, 20, BLACK);
        }
    };
    enum {
        CLOSED,
        TOP,
        MAKE,
        LOAD
    } current_mode = CLOSED;
    std::vector<std::string> level_files();
    std::vector<MenuItem> available_levels;
    static bool in_rect(Rectangle const&r, int x, int y){
        return x >= r.x && x < r.x + r.width && y >= r.y && y < r.y + r.height;
    }

    std::vector<MenuItem> make_load_menu();
    std::function<void(std::string)> load_level;
    std::function<void()> make_level;

    static constexpr Rectangle play_button_rect = {100, 100, 600, 200};
    static constexpr Rectangle make_button_rect = {100, 400, 600, 200};
};


#endif //MARIO_MAKER_MENU_H
