cmake_minimum_required(VERSION 4.0)
project(nhf C)

set(CMAKE_C_STANDARD 11)
if(WIN32)
    set(SDLTTF_VENDORED ON)
endif (WIN32)

add_subdirectory(SDL3)
add_subdirectory(SDL3_image)
add_subdirectory(SDL3_ttf)
add_executable(nhf main.c
        game/menu/menu.c
        game/menu/menu.h
        game/game.h
        game/jatek/jatek.c
        game/jatek/jatek.h
        game/Resume/resume.c
        game/Resume/resume.h
        game/Leaderboard/dicsoseglista.c
        game/Leaderboard/dicsoseglista.h
)
target_link_libraries(nhf PRIVATE SDL3::SDL3 PRIVATE SDL3_image::SDL3_image PRIVATE SDL3_ttf::SDL3_ttf)
add_custom_target(copy_kepek ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/kepek"
        "${CMAKE_BINARY_DIR}/kepek"
)

add_custom_target(copy_music ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Music"
        "${CMAKE_BINARY_DIR}/Music"
)