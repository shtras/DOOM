#ifndef SDL_VIDEO_H
#define SDL_VIDEO_H

#include "doomtype.h"

void SDL_InitGraphics(void);

void SDL_ShutdownGraphics(void);

// Takes full 8 bit values.
void SDL_SetPalette (byte* palette);

void SDL_UpdateNoBlit (void);
void SDL_FinishUpdate (void);

// Wait for vertical retrace or pause a bit.
void SDL_WaitVBL(int count);

void SDL_ReadScreen (byte* scr);

void SDL_BeginRead (void);
void SDL_EndRead (void);

#endif // SDL_VIDEO_H
