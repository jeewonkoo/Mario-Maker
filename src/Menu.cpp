//
// Created by 16182 on 4/5/2022.
//

#include "Menu.h"
#include<filesystem>

std::vector<std::string> Menu::level_files() {
    std::vector<std::string> ret;
    for(auto & f : std::filesystem::directory_iterator{"."}){
        if(f.path().extension() == ".json"){
            ret.push_back(f.path().string());
        }
    }
    return ret;
}
#include<iostream>

std::vector<Menu::MenuItem> Menu::make_load_menu() {
    std::vector<Menu::MenuItem> ret;
    auto files = level_files();
    for(int i = 0; i < files.size(); i++){
        ret.push_back({.rect={100, 100.f+100*i, 200, 50}, .on_click=[=](){load_level(files[i]);}, .name=files[i]});
    }
    return ret;
}
