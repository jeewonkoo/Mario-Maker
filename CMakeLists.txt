cmake_minimum_required(VERSION 3.14)
project(mario_maker)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(raylib)

add_executable(mario_maker src/main.cpp src/Level.cpp src/Mario.cpp)
target_link_libraries(mario_maker PRIVATE raylib)
