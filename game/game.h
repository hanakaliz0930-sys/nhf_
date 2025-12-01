//
// Created by Aliz on 2025. 11. 14..
//

#ifndef NHF_GAME_H
#define NHF_GAME_H
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "Leaderboard/dicsoseglista.h"

typedef struct Jatekos Jatekos;

typedef struct Kepek {
    SDL_Texture *gombok;
    SDL_Texture *hatter;
    SDL_Texture *jatek_hatter;
    SDL_Texture *jatekos;
    SDL_Texture *vendegek;
    SDL_Texture *felkialtojel;
    SDL_Texture *etel;
    SDL_Texture *resume_hatter;
    SDL_Texture *resume_gombok;
    TTF_Font* betutipus;
}Kepek;


typedef enum Allapot {
    FOMENU,START,MUSIC,LEADERBOARD,RESUME,EXIT, NINCS
}Allapot;


typedef struct Jatek {
    Allapot allapot;
    SDL_Renderer* renderer;
    SDL_Window *window;
    SDL_Event event;
    Kepek kepek;
    bool van_zene;
    Jatekos* jatekos;
    SDL_FRect* palya;
    SDL_FRect etelt_hol_vegye_fel;
    bool idozitomegy;
    bool vendeg_letezik[4];
    bool felvette_e_az_etelt;
    bool mikor_kell_kezbe[4];
    bool mentes_volte;
    int pontok;
    SDL_Texture* pont_kep;
    char nev[16];
    SDL_Texture* nev_kep;
    SDL_Texture* ninckname_kep;
    DicsosegLista* dicsoseglista;
}Jatek;

#endif //NHF_GAME_H