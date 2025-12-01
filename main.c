#include <SDL3/SDL.h>
#include <math.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "game/menu/menu.h"
#include "game/game.h"
#include "game/jatek/jatek.h"
#include "SDL3_image/SDL_image.h"
#include <stdbool.h>
#include <time.h>
#include "game/Resume/resume.h"


void texturat_betolt(Jatek *jatek) {
    SDL_Surface* surface = IMG_Load("kepek/gombok.png");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/gombok.png fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.gombok = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("kepek/hatter.jpg");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/hatter.jpg fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.hatter = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("kepek/jatek_hatter.png");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/jatek_hatter.png fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.jatek_hatter = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("kepek/waiter.png");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/waiter.png fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.jatekos = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("kepek/vendegek.png");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/vendegek.png fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.vendegek = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("kepek/felkialtojel.png");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/felkialtojel.png fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.felkialtojel = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("kepek/etel.png");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/etel.png fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.etel = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("kepek/resume_hatter.png");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/resume_hatter.png fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.resume_hatter = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("kepek/resume_gombok.png");
    if (surface == NULL) {
        printf("Nem sikerult betolteni a kepek/resume_gombok.png fajlt.\n");
        exit(1); //leáll a program
    }
    jatek->kepek.resume_gombok = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);


    jatek->kepek.betutipus = TTF_OpenFont("kepek/8-bit-pusab.ttf", 30);
    if (jatek->kepek.betutipus == NULL) {
        printf("Nem sikerult betolteni a kepek/8-bit-pusab.ttf fajlt.\n");
        exit(1); //leáll a program
    }

}

int main(int argc, char *argv[]) {
    srand(time(0));
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("Pinceres jatek", 900, 500, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }

    SDL_AudioStream *stream = NULL;
    Uint8 *wav_data = NULL;
    Uint32 wav_data_len = 0;
    SDL_AudioSpec spec;
    if (!SDL_LoadWAV("Music/zene.wav", &spec, &wav_data, &wav_data_len)) {
        SDL_Log("Nem talalja a wav file-t: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!stream) {
        SDL_Log("Nem tudta letrehozni az audio stream-et: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_ResumeAudioStreamDevice(stream);


    Jatek jatek;
    jatek.allapot = FOMENU;
    jatek.renderer = renderer;
    jatek.van_zene = false;
    jatek.window = window;
    jatek.dicsoseglista = NULL;
    jatek.jatekos = NULL;
    jatek.nev[0] = '\0';

    texturat_betolt(&jatek);
    jatekos_elokeszit(&jatek);
    palya_elokeszit(&jatek);

            /* varunk a kilepesre */
            while (jatek.event.type != SDL_EVENT_QUIT) {


                SDL_PollEvent(&jatek.event);
                SDL_RenderClear(renderer);
                hatter(&jatek);
                if (jatek.van_zene) {
                    if (SDL_GetAudioStreamQueued(stream) < (int)wav_data_len) {
                        SDL_PutAudioStreamData(stream, wav_data, wav_data_len);
                    }
                }
                else {
                    SDL_ClearAudioStream(stream);
                }
                switch (jatek.allapot) {
                    case START:
                        jatek_hatter(&jatek);
                        jatekos(&jatek);
                        
                        break;
                    case FOMENU:
                        //menupontok megjelenitese
                        fomenu(&jatek);
                        break;
                    case MUSIC:
                        back(&jatek);
                        mute_unmute(&jatek);
                        break;
                    case LEADERBOARD:
                        leaderboard_megjelenit(&jatek);
                        back(&jatek);
                        break;
                    case RESUME:
                        resume_hatter(&jatek);
                        resume_gombok(&jatek);
                        jatek.idozitomegy = false;
                        break;
                    case EXIT:
                        exit_vege(&jatek);
                        if (jatek.jatekos != NULL && jatek.palya != NULL) {
                            jatekos_palya_felszabadit(&jatek);
                        }
                        exit(0);
                        break;
                    default:
                        break;
                }

                /* az elvegzett rajzolasok a kepernyore */
                SDL_RenderPresent(renderer);

            }

        jatekos_palya_felszabadit(&jatek);
            /* ablak bezarasa */
            SDL_Quit();

            return 0;
        }