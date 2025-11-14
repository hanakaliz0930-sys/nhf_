//
// Created by Aliz on 2025. 11. 14..
//

#include <stdio.h>
#include <stdlib.h>
#include "../../debugmalloc.h"
#include "SDL3/SDL.h"
#include "../game.h"

typedef struct Gomb {
    Allapot kov_all;
    SDL_FRect rect;
} Gomb;

void fomenu(Jatek *jatek) {
    Gomb gombok[4] = {
        {START, {50, 50, 100, 50}},
        {MUSIC, {50, 150, 100, 50}},
        {LEADERBOARD, {50, 250, 100, 50}},
        {EXIT, {50, 350, 100, 50}}
    };


    for (int i = 0; i < 4; i++) {
        SDL_SetRenderDrawColor(jatek->renderer, 255, 255, 255, 0);
        SDL_RenderFillRect(jatek->renderer, &gombok[i].rect);
        SDL_SetRenderDrawColor(jatek->renderer,0, 0, 0, 0);
    }
    if (jatek->event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (jatek->event.button.button == SDL_BUTTON_LEFT) {
            for (int i = 0; i < 4; i++) {
                if (jatek->event.button.x > gombok[i].rect.x && jatek->event.button.x < 150 && jatek->event.button.y > 50 && jatek->event.button.y < 100) {
                    jatek->allapot = gombok[i].kov_all;
                    printf(":))))))");
                }
                else if (jatek->event.button.x > gombok[i].rect.x && jatek->event.button.x < 150 && jatek->event.button.y > 150 && jatek->event.button.y < 200) {
                    jatek->allapot = gombok[i].kov_all;
                    printf(":))))))");
                }
                else if(jatek->event.button.x > gombok[i].rect.x && jatek->event.button.x < 150 && jatek->event.button.y > 250 && jatek->event.button.y < 300) {
                    jatek->allapot = gombok[i].kov_all;
                    printf(":))))))");
                }
                else if(jatek->event.button.x > gombok[i].rect.x && jatek->event.button.x < 150 && jatek->event.button.y > 350 && jatek->event.button.y < 400) {
                    jatek->allapot = gombok[i].kov_all;
                    printf(":))))))");
                }
            }

        }
    }


}

void back(Jatek *jatek) {
        Gomb vissza = {FOMENU,650,700,100, 50};
        SDL_SetRenderDrawColor(jatek->renderer, 255, 255, 255, 0);
        SDL_RenderFillRect(jatek->renderer, &vissza.rect);
        SDL_SetRenderDrawColor(jatek->renderer,0, 0, 0, 0);
}

