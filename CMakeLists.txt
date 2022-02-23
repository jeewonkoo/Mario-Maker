cmake_minimum_required(VERSION 3.14)
project(mario_maker)


add_subdirectory(raylib)

add_executable(mario_maker src/main.cpp)
target_link_libraries(mario_maker PRIVATE raylib)
