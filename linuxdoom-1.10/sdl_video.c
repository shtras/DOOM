#include "doomdef.h"
#include "v_video.h"
#include "d_event.h"

#include <SDL2/SDL.h>
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

void I_SDL_InitGraphics(void)
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

void I_SDL_SetPalette(byte* palette)
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

void I_SDL_StartFrame(void)
{
}

int xlatekey(SDL_Event* sdl_event)
{
    int rc = sdl_event->key.keysym.sym;

    switch (rc) {
        case SDLK_LEFT:
            rc = KEY_LEFTARROW;
            break;
        case SDLK_RIGHT:
            rc = KEY_RIGHTARROW;
            break;
        case SDLK_DOWN:
            rc = KEY_DOWNARROW;
            break;
        case SDLK_UP:
            rc = KEY_UPARROW;
            break;
        case SDLK_ESCAPE:
            rc = KEY_ESCAPE;
            break;
        case SDLK_RETURN:
            rc = KEY_ENTER;
            break;
        case SDLK_TAB:
            rc = KEY_TAB;
            break;
        case SDLK_F1:
            rc = KEY_F1;
            break;
        case SDLK_F2:
            rc = KEY_F2;
            break;
        case SDLK_F3:
            rc = KEY_F3;
            break;
        case SDLK_F4:
            rc = KEY_F4;
            break;
        case SDLK_F5:
            rc = KEY_F5;
            break;
        case SDLK_F6:
            rc = KEY_F6;
            break;
        case SDLK_F7:
            rc = KEY_F7;
            break;
        case SDLK_F8:
            rc = KEY_F8;
            break;
        case SDLK_F9:
            rc = KEY_F9;
            break;
        case SDLK_F10:
            rc = KEY_F10;
            break;
        case SDLK_F11:
            rc = KEY_F11;
            break;
        case SDLK_F12:
            rc = KEY_F12;
            break;

        case SDLK_BACKSPACE:
        case SDLK_DELETE:
            rc = KEY_BACKSPACE;
            break;

        case SDLK_PAUSE:
            rc = KEY_PAUSE;
            break;

        case SDLK_KP_EQUALS:
        case SDLK_EQUALS:
            rc = KEY_EQUALS;
            break;

        case SDLK_KP_MINUS:
        case SDLK_MINUS:
            rc = KEY_MINUS;
            break;

        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            rc = KEY_RSHIFT;
            break;

        case SDLK_LCTRL:
        case SDLK_RCTRL:
            rc = KEY_RCTRL;
            break;

        case SDLK_LALT:
        case SDLK_RALT:
            rc = KEY_RALT;
            break;

        default:
            if (rc >= SDLK_SPACE && rc <= SDLK_BACKQUOTE) {
                rc = rc - SDLK_SPACE + ' ';
            }
            if (rc >= 'A' && rc <= 'Z') {
                rc = rc - 'A' + 'a';
            }
            break;
    }

    return rc;
}

static int lastmousex = 0;
static int lastmousey = 0;
boolean mousemoved = false;

void I_GetEvent(SDL_Event* sdl_event)
{
    event_t event;
    switch (sdl_event->type) {
        case SDL_KEYDOWN:
            event.type = ev_keydown;
            event.data1 = xlatekey(sdl_event);
            D_PostEvent(&event);
            // fprintf(stderr, "k");
            break;
        case SDL_KEYUP:
            event.type = ev_keyup;
            event.data1 = xlatekey(sdl_event);
            D_PostEvent(&event);
            // fprintf(stderr, "ku");
            break;
        // case SDL_MOUSEBUTTONDOWN:
        //     event.type = ev_mouse;
        //     event.data1 = (X_event.xbutton.state & Button1Mask) |
        //                   (X_event.xbutton.state & Button2Mask ? 2 : 0) |
        //                   (X_event.xbutton.state & Button3Mask ? 4 : 0) |
        //                   (X_event.xbutton.button == Button1) |
        //                   (X_event.xbutton.button == Button2 ? 2 : 0) |
        //                   (X_event.xbutton.button == Button3 ? 4 : 0);
        //     event.data2 = event.data3 = 0;
        //     D_PostEvent(&event);
        //     // fprintf(stderr, "b");
        //     break;
        // case SDL_MOUSEBUTTONUP:
        //     event.type = ev_mouse;
        //     sdl_event->button.
        //     event.data1 = (X_event.xbutton.state & Button1Mask) |
        //                   (X_event.xbutton.state & Button2Mask ? 2 : 0) |
        //                   (X_event.xbutton.state & Button3Mask ? 4 : 0);
        //     // suggest parentheses around arithmetic in operand of |
        //     event.data1 = event.data1 ^ (X_event.xbutton.button == Button1 ? 1 : 0) ^
        //                   (X_event.xbutton.button == Button2 ? 2 : 0) ^
        //                   (X_event.xbutton.button == Button3 ? 4 : 0);
        //     event.data2 = event.data3 = 0;
        //     D_PostEvent(&event);
        //     // fprintf(stderr, "bu");
        //     break;
        // case SDL_MOUSEMOTION:
        //     event.type = ev_mouse;
        //     event.data1 = (X_event.xmotion.state & Button1Mask) |
        //                   (X_event.xmotion.state & Button2Mask ? 2 : 0) |
        //                   (X_event.xmotion.state & Button3Mask ? 4 : 0);
        //     event.data2 = (X_event.xmotion.x - lastmousex) << 2;
        //     event.data3 = (lastmousey - X_event.xmotion.y) << 2;

        //     if (event.data2 || event.data3) {
        //         lastmousex = X_event.xmotion.x;
        //         lastmousey = X_event.xmotion.y;
        //         if (X_event.xmotion.x != X_width / 2 && X_event.xmotion.y != X_height / 2) {
        //             D_PostEvent(&event);
        //             // fprintf(stderr, "m");
        //             mousemoved = false;
        //         } else {
        //             mousemoved = true;
        //         }
        //     }
        //     break;

        // case Expose:
        // case ConfigureNotify:
        //     break;

        // default:
        //     if (doShm && X_event.type == X_shmeventtype) {
        //         shmFinished = true;
        //     }
        //     break;
    }
}

void I_SDL_StartTic(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        I_GetEvent(&event);
    }
}

void I_SDL_UpdateNoBlit(void)
{
}

void I_SDL_FinishUpdate(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    for (int x = 0; x < SCREENWIDTH; x++) {
        for (int y = 0; y < SCREENHEIGHT; y++) {
            byte pixel = screens[0][y * SCREENWIDTH + x];
            SDL_SetRenderDrawColor(
                renderer, colors[pixel].r, colors[pixel].g, colors[pixel].b, colors[pixel].a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);
}
