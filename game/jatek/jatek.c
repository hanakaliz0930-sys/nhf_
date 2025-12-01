//
// Created by Aliz on 2025. 11. 21..
//
#include "jatek.h"
#include <stdlib.h>
#include "../../debugmalloc.h"
#include "../game.h"
#include <time.h>

typedef struct Hivas_fuggveny_param {
        int i;
        Jatek *jatek;
} Hivas_fuggveny_param;


Uint32 visszahivas(void* adat, SDL_TimerID idozito_ID, Uint32 intervallum) {
        Jatek* jatek = (Jatek*)adat;
        SDL_StartTextInput(jatek->window);
        jatek->allapot = RESUME;
        return 0;
}

Uint32 jatekos_eltunik_hivasa(void* adat, SDL_TimerID idozito_ID, Uint32 intervallum) {
        Hivas_fuggveny_param* parameterek = (Hivas_fuggveny_param*)adat;
        parameterek->jatek->vendeg_letezik[parameterek->i] = false;
        parameterek->jatek->mikor_kell_kezbe[parameterek->i] = false;
        free(parameterek);
        return 0;
}

void jatek_hatter(Jatek *jatek) {
        SDL_RenderTexture(jatek->renderer, jatek->kepek.jatek_hatter, NULL, NULL);
        vendegek(jatek);
        etel(jatek);
        if (!jatek->idozitomegy) {
                SDL_AddTimer(60000, visszahivas, jatek);
                jatek->idozitomegy = true;
        }
        SDL_FRect cel_betu = {10, 30, 11*20, 30};
        SDL_RenderTexture(jatek->renderer, jatek->pont_kep,NULL, &cel_betu);
}
bool atfedes(SDL_FRect a, SDL_FRect b)
{
        return (a.x < b.x + b.w &&
                a.x + a.w > b.x &&
                a.y < b.y + b.h &&
                a.y + a.h > b.y);
}

void jatekos(Jatek *jatek) {
        SDL_RenderTexture(jatek->renderer, jatek->kepek.jatekos, &jatek->jatekos->jatekosforras , &jatek->jatekos->jatekoskoordinata);
        if (jatek->event.type == SDL_EVENT_KEY_DOWN) {
                        if (jatek->event.key.key == SDLK_W || jatek->event.key.key == SDLK_UP) {
                                bool mehet = true;
                                SDL_FRect kovetkezo_poz = jatek->jatekos->jatekoskoordinata;
                                kovetkezo_poz.y -= 13;

                                for (int i = 0; i < 25; i++) {
                                        if (atfedes(kovetkezo_poz, jatek->palya[i])) {
                                                mehet = false;
                                                break;
                                        }
                                }
                                if (mehet) {
                                        jatek->jatekos->jatekosforras.x = 3;
                                        jatek->jatekos->jatekosforras.y = 289;
                                        jatek->jatekos->jatekoskoordinata = kovetkezo_poz;
                                }
                        }
                        if (jatek->event.key.key == SDLK_D || jatek->event.key.key == SDLK_RIGHT) {
                                bool mehet = true;
                                SDL_FRect kovetkezo_poz = jatek->jatekos->jatekoskoordinata;
                                kovetkezo_poz.x += 13;
                                for (int i = 0; i < 25; i++) {
                                        if (atfedes(kovetkezo_poz, jatek->palya[i])) {
                                                mehet = false;
                                                break;
                                        }
                                }
                                         if (mehet) {
                                                 jatek->jatekos->jatekosforras.x = 3;
                                                 jatek->jatekos->jatekosforras.y = 196;
                                                 jatek->jatekos->jatekoskoordinata = kovetkezo_poz;
                                         }

                        }
                        if (jatek->event.key.key == SDLK_A || jatek->event.key.key == SDLK_LEFT) {
                                bool mehet = true;
                                SDL_FRect kovetkezo_poz = jatek->jatekos->jatekoskoordinata;
                                kovetkezo_poz.x -= 13;
                                for (int i = 0; i < 25; i++) {
                                        if (atfedes(kovetkezo_poz, jatek->palya[i])) {
                                                mehet = false;
                                                break;
                                        }
                                }
                                if (mehet) {
                                        jatek->jatekos->jatekosforras.x = 3;
                                        jatek->jatekos->jatekosforras.y = 102;
                                        jatek->jatekos->jatekoskoordinata = kovetkezo_poz;
                                }

                        }
                        if (jatek->event.key.key == SDLK_S || jatek->event.key.key == SDLK_DOWN) {
                                bool mehet = true;
                                SDL_FRect kovetkezo_poz = jatek->jatekos->jatekoskoordinata;
                                kovetkezo_poz.y += 13;
                                for (int i = 0; i < 25; i++) {
                                        if (atfedes(kovetkezo_poz, jatek->palya[i])) {
                                                mehet = false;
                                                break;
                                        }
                                }
                                        if (mehet){
                                                jatek->jatekos->jatekosforras.x = 3;
                                                jatek->jatekos->jatekosforras.y = 8;
                                                jatek->jatekos->jatekoskoordinata = kovetkezo_poz;
                                        }
                        }
        }

}

void jatekos_elokeszit(Jatek *jatek){
        jatek->jatekos = malloc(sizeof(Jatekos));
        jatek->jatekos->jatekosforras.x = 3;
        jatek->jatekos->jatekosforras.y = 8;
        jatek->jatekos->jatekosforras.w = 56;
        jatek->jatekos->jatekosforras.h = 83;


        jatek->jatekos->jatekoskoordinata.x = 440;
        jatek->jatekos->jatekoskoordinata.y = 209;
        jatek->jatekos->jatekoskoordinata.w = 56;
        jatek->jatekos->jatekoskoordinata.h = 83;
        jatek->idozitomegy = false;
        jatek->mentes_volte = false;
        jatek->pontok = 0;
        for (int i = 0; i < 4; i++) {
                jatek->mikor_kell_kezbe[i] = false;
        }
}
void palya_elokeszit(Jatek *jatek) {
        jatek->palya = malloc(sizeof(SDL_FRect) * 25);
        jatek->palya[0] = (SDL_FRect) {0,0,930,150};
        jatek->palya[1] = (SDL_FRect) {569,344,148,56};
        jatek->palya[2] = (SDL_FRect) {717,401,36,1};
        jatek->palya[3] = (SDL_FRect) {196,113,244,134};
        jatek->palya[4] = (SDL_FRect) {507,113,94,134};
        jatek->palya[5] = (SDL_FRect) {280,380,150,15};
        jatek->palya[6] = (SDL_FRect) {387,339,22,51};
        jatek->palya[7] = (SDL_FRect) {44,380,148,21};
        jatek->palya[8] = (SDL_FRect) {195,390,31,14};
        jatek->palya[9] = (SDL_FRect) {36,127,114,10};
        jatek->palya[10] = (SDL_FRect) {439,402,30,6};
        jatek->palya[11] = (SDL_FRect) {298,339,37,40};
        jatek->palya[12] = (SDL_FRect) {140,345,27,39};
        jatek->palya[13] = (SDL_FRect) {57,346,30,31};
        jatek->palya[14] = (SDL_FRect) {210,274,44,12};
        jatek->palya[15] = (SDL_FRect) {337,270,32,17};
        jatek->palya[16] = (SDL_FRect) {624,201,35,16};
        jatek->palya[17] = (SDL_FRect) {547,274,26,5};
        jatek->palya[18] = (SDL_FRect) {576,304,24,28};
        jatek->palya[19] = (SDL_FRect) {675,304,20,30};
        jatek->palya[20] = (SDL_FRect) {852,381,48,26};
        jatek->palya[21] = (SDL_FRect) {877,338,22,41};
        jatek->palya[22] = (SDL_FRect) {730,107,110,13};
        jatek->palya[23] = (SDL_FRect) {810,242,90,22};
        jatek->palya[24] = (SDL_FRect) {830,201,29,39};
        jatek->felvette_e_az_etelt = false;
}


void vendegek(Jatek *jatek) {
        SDL_FRect vendegforras_koordinatak[4] = {{29,24,64,148},{147, 31,60,152}, {49, 197, 42, 69}, {39,282, 62, 86}};
        SDL_FRect vendeg_ulo_koordinatak[4] = {{219,174, 64,148}, {522,176,60,152}, {579, 277, 42, 69}, {651,259,62, 86}};
        SDL_FRect vendeg_kezbe[4] = {{248,251,45,30},{488,252,45,30}, {581, 326, 45, 30},{659,327,45,30}};
        SDL_FRect etel_forras = {419,176,3219,2397};
        SDL_FRect felkialtojel_koordinatak = {85, 20, 89, 220};

        int vendeg_letezik_db = 0;
        for (int i = 0; i < 4; i++) {
                if (jatek->vendeg_letezik[i]) vendeg_letezik_db++;
        }
        int j = rand() % 4;
        if (!jatek->vendeg_letezik[j] && vendeg_letezik_db < 3) {
                jatek->vendeg_letezik[j] = (rand() % 100 < 2 ? true : false);
        }

        SDL_FRect felkialtojel_cel[4];

        for (int i = 0; i < 4; i++) {
                if (jatek->vendeg_letezik[i]){
                        SDL_RenderTexture(jatek->renderer, jatek->kepek.vendegek, &vendegforras_koordinatak[i] , &vendeg_ulo_koordinatak[i]);
                        felkialtojel_cel[i] = (SDL_FRect) {vendeg_ulo_koordinatak[i].x + (vendeg_ulo_koordinatak[i].w / 4), vendeg_ulo_koordinatak[i].y - 50 ,20, 50};
                        if (!jatek->mikor_kell_kezbe[i]) {
                                SDL_RenderTexture(jatek->renderer, jatek->kepek.felkialtojel,&felkialtojel_koordinatak , &felkialtojel_cel[i]);
                        }
                        // SDL_SetRenderDrawColor(jatek->renderer, 255, 0, 0,0);
                        //SDL_RenderFillRect(jatek->renderer, &felkialtojel_cel);
                }
        }

        SDL_FRect jatekos_nagy_hitbox = jatek->jatekos->jatekoskoordinata;
        jatekos_nagy_hitbox.x -= 20;
        jatekos_nagy_hitbox.y -= 20;
        jatekos_nagy_hitbox.w += 40;
        jatekos_nagy_hitbox.h += 40;

        for (int i = 0; i < 4; i++) {
                if (SDL_HasRectIntersectionFloat(&jatekos_nagy_hitbox, &vendeg_ulo_koordinatak[i]) && jatek->felvette_e_az_etelt && !jatek->mikor_kell_kezbe[i] && jatek->vendeg_letezik[i]) {
                        jatek->felvette_e_az_etelt = false;
                        etel_kezbe(jatek, &vendeg_ulo_koordinatak[i]);
                        jatek->pontok++;
                        char szoveg[11];
                        sprintf(szoveg, "%d points", jatek->pontok);
                        SDL_Color szin = {255, 255, 255, 255};
                        SDL_Surface* surface = TTF_RenderText_Blended(jatek->kepek.betutipus, szoveg, 0, szin);
                        jatek->pont_kep = SDL_CreateTextureFromSurface(jatek->renderer, surface);
                        SDL_DestroySurface(surface);
                        Hivas_fuggveny_param* parameterek = malloc(sizeof(Hivas_fuggveny_param));
                        parameterek->i = i;
                        parameterek->jatek = jatek;
                        SDL_AddTimer(10000, jatekos_eltunik_hivasa, parameterek);
                        jatek->mikor_kell_kezbe[i] = true;

                }
                if (jatek->mikor_kell_kezbe[i]) {
                        SDL_RenderTexture(jatek->renderer, jatek->kepek.etel,&etel_forras , &vendeg_kezbe[i]);
                }
        }
}



void etel(Jatek *jatek) {
        SDL_FRect etel_forras = {419,176,3219,2397};
        SDL_FRect etel_cel = {198,143, 45, 30};
        SDL_RenderTexture(jatek->renderer, jatek->kepek.etel, &etel_forras , &etel_cel);


        jatek->etelt_hol_vegye_fel = (SDL_FRect) {160,105,90,70};

                if (SDL_HasRectIntersectionFloat(&jatek->etelt_hol_vegye_fel, &jatek->jatekos->jatekoskoordinata)) {
                        jatek->felvette_e_az_etelt = true;
                }
        if (jatek->felvette_e_az_etelt) {
                etel_cel.x = jatek->jatekos->jatekoskoordinata.x + 8;
                etel_cel.y = jatek->jatekos->jatekoskoordinata.y - 22;
                etel_cel.w = 45;
                etel_cel.h = 30;
        }
        SDL_RenderTexture(jatek->renderer, jatek->kepek.etel, &etel_forras, &etel_cel);
}

void etel_kezbe(Jatek *jatek, SDL_FRect *vendeg_koordinatak) {
        SDL_FRect etel_forras = {419,176,3219,2397};
        SDL_FRect etel_megjelenik = {
                vendeg_koordinatak->x,
                vendeg_koordinatak->y - (vendeg_koordinatak->h)/2,
                45,
                30
        };
        SDL_RenderTexture(jatek->renderer, jatek->kepek.etel, &etel_forras, &etel_megjelenik);
}

void jatekos_palya_felszabadit(Jatek *jatek) {
        free(jatek->jatekos);
        jatek->jatekos = NULL;
        free(jatek->palya);
        jatek->palya = NULL;
}



























