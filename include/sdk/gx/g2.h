#ifndef SDK_GX_G2_H
#define SDK_GX_G2_H

// TwlSDK G2 background helpers: screen and character base addresses of the backgrounds, blend registers.
#include "types.h"

extern "C" {
void *G2_GetBG0ScrPtr(void);
void *G2S_GetBG0ScrPtr(void);
void *G2_GetBG1ScrPtr(void);
void *G2S_GetBG1ScrPtr(void);
void *G2_GetBG0CharPtr(void);
void *G2S_GetBG0CharPtr(void);
void *G2_GetBG1CharPtr(void);
void *G2S_GetBG1CharPtr(void);
void G2x_SetBlendAlpha_(void *reg, s32 plane1, s32 plane2, s32 ev1, s32 ev2);
}

#endif
