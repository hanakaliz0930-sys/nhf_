//
// Created by Aliz on 2025. 11. 14..
//

#include <stdio.h>
#include <stdlib.h>
#include "../../debugmalloc.h"
#include "SDL3/SDL.h"
#include "../game.h"
#include "debugmalloc.h"

// itt van a gomb típusa
typedef struct Gomb {
    Allapot kov_all;
    SDL_FRect rect;
    SDL_FRect textura_koordinata;
} Gomb;

typedef struct Gomb_mute {
    bool klikkelte;
    SDL_FRect rect;
    SDL_FRect textura_koordinata;
} Gomb_mute;

void fomenu(Jatek *jatek) {
    // létrehozom a főmenüben lévő pontokat, koordinátáit, szélességét, magasságát megadom, továbbá
    // hogy milyen állapotba vigyen, ha megnyomtam a gombot.
    Gomb fomenupontok[4] = {
        {START, {50, 50, 100, 50}, {0,0, 209, 63}},
        {MUSIC, {50, 150, 100, 50},{0,63,194,63}},
        {LEADERBOARD, {50, 250, 100, 50}, {0,263,198,93}},
        {EXIT, {50, 350, 100, 50},{0,433,175,86}}
    };




    /*
     * mivel most a főmenüben vagyok létrehozom a gombokat
     * 4 gomb van, tehát 4szer kell lefusson a ciklus
     */
    for (int i = 0; i < 4; i++) {
        SDL_SetRenderDrawColor(jatek->renderer, 255, 255, 255, 0);
        //SDL_RenderFillRect(jatek->renderer, &fomenupontok[i].rect);
        SDL_RenderTexture(jatek->renderer, jatek->kepek.gombok, &fomenupontok[i].textura_koordinata , &fomenupontok[i].rect);
        SDL_SetRenderDrawColor(jatek->renderer,0, 0, 0, 0);
    }
    // ha megnyomtam az aktuális gombot
    if (jatek->event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (jatek->event.button.button == SDL_BUTTON_LEFT) {
            int iykezdet = 50;
            int iyveg = 100;
            //itt azért kellenek változók, mert a gombok koordinátái különbözők, de egyikből kiszámíthatom a másikat, mert sorba vannak
            for (int i = 0; i < 4; i++) {
                //a ciklus 4szer fut le, mert 4 gomb van
                if (jatek->event.button.x > fomenupontok[i].rect.x && jatek->event.button.x < 150 && jatek->event.button.y > iykezdet && jatek->event.button.y < iyveg) {
                    jatek->allapot = fomenupontok[i].kov_all;
                }
                iykezdet+=100;
                iyveg+=100;
            }

        }
    }
}
void hatter(Jatek *jatek) {
    if (jatek->allapot != START && jatek->allapot != EXIT) {
            SDL_RenderTexture(jatek->renderer, jatek->kepek.hatter, NULL, NULL);
    }
}

void back(Jatek *jatek) {

    /*
     * itt a back gombot hozom létre, ami vissza visz a főmenübe
     * létre hozom a gombot és megadom a koordinátákat
     * |
     * v
     */
    Gomb vissza = {FOMENU,700,350,100, 50, {0,356,171,78}}; // itt is azért kell a főmenüre hivatkozni
    SDL_SetRenderDrawColor(jatek->renderer, 255, 255, 255, 0);
    //SDL_RenderFillRect(jatek->renderer, &vissza.rect);
    SDL_RenderTexture(jatek->renderer, jatek->kepek.gombok, &vissza.textura_koordinata, &vissza.rect);
    SDL_SetRenderDrawColor(jatek->renderer,0, 0, 0, 0);

    //ha megnyomtam a gombot
    if (jatek->event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (jatek->event.button.button == SDL_BUTTON_LEFT) {
            if (jatek->event.button.x > vissza.rect.x && jatek->event.button.x < 800 && jatek->event.button.y > 350 && jatek->event.button.y < 400) {
                jatek->allapot = vissza.kov_all; // akkor a főmenübe vigyen
            }
        }
    }
}
void klikkelte_mute(Jatek *jatek, Gomb_mute* mute) {
    if (jatek->event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (jatek->event.button.button == SDL_BUTTON_LEFT) {

            for (int i = 0; i < 2; i++) {
                if (jatek->event.button.x > mute[i].rect.x && jatek->event.button.x < mute[i].rect.x + mute[i].rect.w   &&
                    jatek->event.button.y > mute[i].rect.y && jatek->event.button.y < mute[i].rect.y + mute[i].rect.h)
                {
                    jatek->van_zene = mute[i].klikkelte;
                }
            }
        }
    }
}

void mute_unmute(Jatek *jatek) {
    Gomb_mute mute[2] = {
        {false, 50, 150, 100, 50,{1, 126,195,70}},
{true, 50, 250, 100, 50, {1, 196,197,67}}};
    for (int i = 0; i < 2; i++) {
        SDL_SetRenderDrawColor(jatek->renderer, 255, 255, 255, 0);
        //SDL_RenderFillRect(jatek->renderer, &mute[i].rect);
        SDL_RenderTexture(jatek->renderer, jatek->kepek.gombok,&mute[i].textura_koordinata,&mute[i].rect);
        SDL_SetRenderDrawColor(jatek->renderer,0, 0, 0, 0);
    }



        klikkelte_mute(jatek, mute);

}

void zenelegyen() {


}

void exit_vege(Jatek *jatek) {
  SDL_DestroyRenderer(jatek->renderer);
    SDL_DestroyTexture(jatek->kepek.gombok);
    SDL_DestroyTexture(jatek->kepek.hatter);
}


