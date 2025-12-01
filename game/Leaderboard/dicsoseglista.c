//
// Created by Aliz on 2025. 11. 30..
//

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../game.h"
#include "dicsoseglista.h"
#include "../../debugmalloc.h"


DicsosegLista* uj_elem(const char* nev, int pont, Jatek* jatek)
{
    DicsosegLista* uj = malloc(sizeof(DicsosegLista));
    if (!uj) return NULL;

    strncpy(uj->nev, nev, 14);
    uj->nev[14] = '\0';
    uj->pont = pont;
    uj->kov = NULL;

    SDL_Color fekete = {0, 0, 0, 255};

    SDL_Surface* surface = TTF_RenderText_Blended(jatek->kepek.betutipus, uj->nev, 0, fekete);
    uj->nev_kep = SDL_CreateTextureFromSurface(jatek->renderer, surface);
    SDL_DestroySurface(surface);

    char pontnak_a_szovege[16];
    snprintf(pontnak_a_szovege, sizeof(pontnak_a_szovege), "%d", pont);

    SDL_Surface* surface2 = TTF_RenderText_Blended(jatek->kepek.betutipus, pontnak_a_szovege, 0, fekete);
    uj->pont_kep = SDL_CreateTextureFromSurface(jatek->renderer, surface2);
    SDL_DestroySurface(surface2);

    return uj;
}


DicsosegLista* dicsoseg_beolvas(Jatek* jatek)
{
    FILE* f = fopen("szoveg.txt", "r");
    if (!f) return NULL;

    DicsosegLista *elso = NULL, *utolso = NULL;
    char sor[128];

    while (fgets(sor, sizeof(sor), f))
    {
        int pont;
        char nev[50];

        if (sscanf(sor, "%d;%49s", &pont, nev) != 2)
            continue;

        DicsosegLista* uj = uj_elem(nev, pont, jatek);
        if (!uj) continue;

        if (!elso) elso = uj;
        else utolso->kov = uj;

        utolso = uj;
    }

    fclose(f);
    return elso;
}


void dicsoseg_rendez(DicsosegLista* head)
{
    if (!head) return;

    bool csere;
    DicsosegLista *a, *b;

    do {
        csere = false;
        a = head;

        while (a->kov) {
            b = a->kov;

            if (a->pont < b->pont) {

                char nevTmp[15];
                strcpy(nevTmp, a->nev);
                strcpy(a->nev, b->nev);
                strcpy(b->nev, nevTmp);

                int p = a->pont;
                a->pont = b->pont;
                b->pont = p;

                SDL_Texture* t = a->nev_kep;
                a->nev_kep = b->nev_kep;
                b->nev_kep = t;

                t = a->pont_kep;
                a->pont_kep = b->pont_kep;
                b->pont_kep = t;

                csere = true;
            }
            a = a->kov;
        }

    } while (csere);
}


void dicsoseg_rajzol(Jatek* jatek, DicsosegLista* head)
{
    int x = 150;
    int y = 120;
    int sor_koz = 50;
    int db = 0;

    for (DicsosegLista* p = head; p != NULL && db < 5; p = p->kov)
    {
        SDL_FRect hova_nev  = { x,       y, strlen(p->nev)*20, 30 };
        SDL_FRect hova_pont = { x + 300, y, 3*20, 30};

        SDL_RenderTexture(jatek->renderer, p->nev_kep,  NULL, &hova_nev);
        SDL_RenderTexture(jatek->renderer, p->pont_kep, NULL, &hova_pont);

        y += sor_koz;
        db++;
    }
}


void dicsoseg_free(DicsosegLista* head)
{
    while (head) {
        DicsosegLista* kov = head->kov;

        if (head->nev_kep) SDL_DestroyTexture(head->nev_kep);
        if (head->pont_kep) SDL_DestroyTexture(head->pont_kep);

        free(head);
        head = kov;
    }
}

void leaderboard_megjelenit(Jatek* jatek)
{
    if (jatek->dicsoseglista == NULL)
    {
        jatek->dicsoseglista = dicsoseg_beolvas(jatek);

        if (!jatek->dicsoseglista)
            return;

        dicsoseg_rendez(jatek->dicsoseglista);
    }

    dicsoseg_rajzol(jatek, jatek->dicsoseglista);
}
