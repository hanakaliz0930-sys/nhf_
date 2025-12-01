//
// Created by Aliz on 2025. 11. 30..
//

#ifndef NHF_DICSOSEGLISTA_H
#define NHF_DICSOSEGLISTA_H

typedef struct Jatek Jatek;

typedef struct DicsosegLista {
    char nev[15];
    int pont;
    SDL_Texture* nev_kep;
    SDL_Texture* pont_kep;
    struct DicsosegLista* kov;
} DicsosegLista;

void leaderboard_megjelenit(Jatek* jatek);
void dicsoseg_free(DicsosegLista* head);

#endif //NHF_DICSOSEGLISTA_H