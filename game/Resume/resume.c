//
// Created by Aliz on 2025. 11. 25..
//
#include  <stdio.h>
#include <stdlib.h>
#include "../game.h"
#include "SDL3/SDL.h"
#include "resume.h"
#include "../../debugmalloc.h"

typedef struct Gomb {
        Allapot kov_all;
        SDL_FRect forras_koordinata;
        SDL_FRect megjelenites_koordinata;
} Gomb;

void resume_hatter(Jatek* jatek) {
        SDL_RenderTexture(jatek->renderer, jatek->kepek.resume_hatter, NULL, NULL);
        SDL_FRect nev_koordinata = {490, 250, strlen(jatek->nev)*20, 30};
        SDL_FRect nickname_koordinata = {490, 150, strlen("nickname\0")*20, 30};
        SDL_Color szin = {255, 255, 255, 255};
        SDL_RenderFillRect(jatek->renderer, &nickname_koordinata);
        SDL_Surface* s2 = TTF_RenderText_Blended(jatek->kepek.betutipus, "nickname\0", 0, szin);
        SDL_RenderTexture(jatek->renderer, jatek->ninckname_kep, NULL, &nickname_koordinata);
        jatek->ninckname_kep = SDL_CreateTextureFromSurface(jatek->renderer, s2);
        SDL_DestroySurface(s2);
        SDL_SetRenderDrawColor(jatek->renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(jatek->renderer, &nev_koordinata);
        SDL_RenderTexture(jatek->renderer, jatek->nev_kep, NULL, &nev_koordinata);
        if (jatek->event.type == SDL_EVENT_TEXT_INPUT) {
                if (strlen(jatek->nev) + 1 < sizeof(jatek->nev)) {
                        strcat(jatek->nev, jatek->event.text.text);
                        SDL_Surface* s = TTF_RenderText_Blended(jatek->kepek.betutipus, jatek->nev, 0, szin);
                        jatek->nev_kep = SDL_CreateTextureFromSurface(jatek->renderer, s);
                        SDL_DestroySurface(s);
                }
        }

}
void resume_gombok(Jatek* jatek) {
        Gomb gomb[3] = {
                {FOMENU, {6,73, 581, 198},{50,40,290,99}},
                {NINCS, {8, 277,560,188}, {50,40,280,94}},
                {EXIT, {8,485,566,195}, {50,40,283, 97}}
        };

        for (int i = 1; i < 3; i++) {
                gomb[i].megjelenites_koordinata.y = gomb[i-1].megjelenites_koordinata.y + 130;
        }
        SDL_FRect pont_kiiras_hely = {16,150,11*20, 30};

        SDL_RenderTexture(jatek->renderer, jatek->pont_kep,NULL, &pont_kiiras_hely);
        SDL_SetRenderDrawColor(jatek->renderer, 255, 255, 255, 0);
        //SDL_RenderFillRect(jatek->renderer, &vissza.rect);
        for (int i = 0; i < 3; i++) {
                SDL_RenderTexture(jatek->renderer, jatek->kepek.resume_gombok, &gomb[i].forras_koordinata, &gomb[i].megjelenites_koordinata);
        }
        SDL_SetRenderDrawColor(jatek->renderer,0, 0, 0, 0);


        if (jatek->event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && jatek->event.button.button == SDL_BUTTON_LEFT) {
                        for (int i = 0; i < 3; i++) {
                                if (jatek->event.button.x > gomb[i].megjelenites_koordinata.x && jatek->event.button.x < (gomb[i].megjelenites_koordinata.x + gomb[i].megjelenites_koordinata.w) && jatek->event.button.y > gomb[i].megjelenites_koordinata.y && jatek->event.button.y < (gomb[i].megjelenites_koordinata.y + gomb[i].megjelenites_koordinata.h)) {
                                        if (gomb[i].kov_all == NINCS) {
                                                FILE *fp;

                                                fp = fopen("szoveg.txt", "a+");
                                                if (fp == NULL) {
                                                        perror("Fájl megnyitása sikertelen");
                                                        return;
                                                }
                                                fprintf(fp, "%d;%s\n", jatek->pontok, jatek->nev);
                                                fclose(fp);
                                                SDL_StopTextInput(jatek->window);
                                                jatek->allapot = FOMENU;
                                        }
                                        else {
                                                jatek->allapot = gomb[i].kov_all;
                                        }
                                        jatek->pontok = 0;
                                        jatek->pont_kep = NULL;
                                        strcpy(jatek->nev, "");
                                        jatek->nev_kep = NULL;
                                        jatek->felvette_e_az_etelt = false;
                                        for (int i = 0; i < 4; i++) {
                                                jatek->mikor_kell_kezbe[i] = false;
                                        }
                                }
                        }
        }
}