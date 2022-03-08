cmake_minimum_required(VERSION 3.14)
project(mario_maker)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(raylib)

add_executable(mario_maker
        src/main.cpp
        src/TileGrid.cpp
        src/Mario.cpp
        src/enemies/Goomba.cpp
        src/Tile.h
        src/Entity.h
        src/Level.cpp
        src/Level.h
        src/InputState.h 
        src/powerups/Mushroom.cpp 
        src/powerups/Mushroom.h
          )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-missing-field-initializers")

target_link_libraries(mario_maker PRIVATE raylib)