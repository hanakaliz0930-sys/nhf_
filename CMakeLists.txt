cmake_minimum_required(VERSION 4.0)
project(nhf C)

set(CMAKE_C_STANDARD 11)
add_subdirectory(SDL3)
add_executable(nhf main.c
        game/menu/menu.c
        game/menu/menu.h
        game/game.h)
target_link_libraries(nhf PRIVATE SDL3::SDL3)