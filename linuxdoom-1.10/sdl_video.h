#ifndef SDL_VIDEO_H
#define SDL_VIDEO_H

#include "doomtype.h"

void I_SDL_InitGraphics(void);

void I_SDL_ShutdownGraphics(void);

// Takes full 8 bit values.
void I_SDL_SetPalette (byte* palette);

void I_SDL_UpdateNoBlit (void);
void I_SDL_FinishUpdate (void);

// Wait for vertical retrace or pause a bit.
void I_SDL_WaitVBL(int count);

void I_SDL_ReadScreen (byte* scr);

void I_SDL_BeginRead (void);
void I_SDL_EndRead (void);

#endif // SDL_VIDEO_H
