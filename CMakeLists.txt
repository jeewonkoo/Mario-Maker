cmake_minimum_required(VERSION 3.14)
project(mario_maker)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(raylib)

set(mario_src
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
    src/enemies/Boo.cpp
    src/enemies/Boo.h
    src/powerups/TanookieLeaf.cpp
    src/powerups/TanookieLeaf.h
    src/powerups/SmallShroom.cpp
    src/powerups/SmallShroom.h
    src/BuilderUI.cpp
    src/BuilderUI.h)

add_executable(mario_maker
        src/main.cpp
        ${mario_src}
        )

add_executable(tests
    tests/catch.cc
    ${mario_src})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
target_link_libraries(mario_maker PRIVATE raylib)
target_link_libraries(tests PRIVATE raylib)