#include <SDL3/SDL.h>
#include <math.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "game/menu/menu.h"
#include "game/game.h"

int main(int argc, char *argv[]) {
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", 900, 500, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }

    Jatek jatek;
    jatek.allapot = FOMENU;
    jatek.renderer = renderer;


    /* varunk a kilepesre */
    while (jatek.event.type != SDL_EVENT_QUIT) {
        /* SDL_RenderPresent(renderer);*/
        SDL_PollEvent(&jatek.event);
        SDL_RenderClear(renderer);

        switch (jatek.allapot) {
            case FOMENU:
                //menupontok megjelenitese
                fomenu(&jatek);
                break;
            case MUSIC:
                back(&jatek);
                break;
            case LEADERBOARD:
                back(&jatek);
                break;
            default:
                break;
        }


        /* az elvegzett rajzolasok a kepernyore */
        SDL_RenderPresent(renderer);

    }


    /* ablak bezarasa */
    SDL_Quit();

    return 0;
}