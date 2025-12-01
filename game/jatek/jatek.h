//
// Created by Aliz on 2025. 11. 21..
//

#ifndef NHF_JATEK_H
#define NHF_JATEK_H
#include "../game.h"

typedef struct Jatekos {
    SDL_FRect jatekosforras;
    SDL_FRect jatekoskoordinata;
}Jatekos;

void jatek_hatter(Jatek* jatek);
void jatekos(Jatek *jatek);
void jatekos_elokeszit(Jatek *jatek);
void palya_elokeszit(Jatek *jatek);
void jatekos_palya_felszabadit(Jatek *jatek);
void vendegek(Jatek *jatek);
void etel_kezbe(Jatek *jatek, SDL_FRect *vendeg_koordinatak);
void etel(Jatek *jatek);
#endif //NHF_JATEK_H