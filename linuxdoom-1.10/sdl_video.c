#include "doomdef.h"
#include "v_video.h"

#include <SDL.h>
SDL_Window* window;
SDL_Renderer* renderer;
struct color_t
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

struct color_t colors[256];

void SDL_InitGraphics(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(
        "Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, 0);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < SCREENWIDTH; ++i) {
        SDL_RenderDrawPoint(renderer, i, i);
    }
    SDL_RenderPresent(renderer);
}

void SDL_SetPalette(byte* palette)
{
    int c;
    for (int i = 0; i < 256; ++i) {
        c = gammatable[usegamma][*palette++];
        colors[i].r = (c << 8) + c;
        c = gammatable[usegamma][*palette++];
        colors[i].g = (c << 8) + c;
        c = gammatable[usegamma][*palette++];
        colors[i].b = (c << 8) + c;
        colors[i].a = 255;
    }
}

void SDL_StartFrame(void)
{
}

void SDL_StartTic(void)
{
}

void SDL_UpdateNoBlit(void)
{
}

void SDL_FinishUpdate(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    for (int x = 0; x < SCREENWIDTH; x++) {
        for (int y = 0; y < SCREENHEIGHT; y++) {
            byte pixel = screens[0][y * SCREENWIDTH + x];
            SDL_SetRenderDrawColor(renderer, colors[pixel].r, colors[pixel].g, colors[pixel].b, colors[pixel].a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);
}
