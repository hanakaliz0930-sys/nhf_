//
// Created by Aliz on 2025. 11. 25..
//
#include  <stdio.h>
#include <stdlib.h>
#include "../game.h"
#include "SDL3/SDL.h"
#include "resume.h"

typedef struct Gomb {
        Allapot kov_all;
        SDL_FRect forras_koordinata;
        SDL_FRect megjelenites_koordinata;
} Gomb;

void resume_hatter(Jatek* jatek) {
        SDL_RenderTexture(jatek->renderer, jatek->kepek.resume_hatter, NULL, NULL);
}
void resume_gombok(Jatek* jatek) {
        Gomb gomb[3] = {
                {FOMENU, {6,73, 581, 198},{50,40,290,99}},
                {LEADERBOARD, {8, 277,560,188}, {50,40,280,94}},
                {EXIT, {8,485,566,195}, {50,40,283, 97}}
        };
        for (int i = 1; i < 3; i++) {
                gomb[i].megjelenites_koordinata.y = gomb[i-1].megjelenites_koordinata.y + 130;
        }

        SDL_SetRenderDrawColor(jatek->renderer, 255, 255, 255, 0);
        //SDL_RenderFillRect(jatek->renderer, &vissza.rect);
        for (int i = 0; i < 3; i++) {
                SDL_RenderTexture(jatek->renderer, jatek->kepek.resume_gombok, &gomb[i].forras_koordinata, &gomb[i].megjelenites_koordinata);
        }
        SDL_SetRenderDrawColor(jatek->renderer,0, 0, 0, 0);


        if (jatek->event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && jatek->event.button.button == SDL_BUTTON_LEFT) {
                        for (int i = 0; i < 3; i++) {
                                //a ciklus 3szor fut le, mert 3 gomb van
                                if (jatek->event.button.x > gomb[i].megjelenites_koordinata.x && jatek->event.button.x < (gomb[i].megjelenites_koordinata.x + gomb[i].megjelenites_koordinata.w) && jatek->event.button.y > gomb[i].megjelenites_koordinata.y && jatek->event.button.y < (gomb[i].megjelenites_koordinata.y + gomb[i].megjelenites_koordinata.h)) {
                                        jatek->allapot = gomb[i].kov_all;
                                }
                        }
        }
}