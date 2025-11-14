//
// Created by Aliz on 2025. 11. 14..
//

#ifndef NHF_GAME_H
#define NHF_GAME_H
#include "SDL3/SDL.h"

typedef enum Allapot {
    FOMENU,START,MUSIC,LEADERBOARD,EXIT
}Allapot;

typedef struct Jatek {
    Allapot allapot;
    SDL_Renderer* renderer;
    SDL_Event event;
}Jatek;

#endif //NHF_GAME_H