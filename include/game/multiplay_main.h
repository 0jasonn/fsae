#ifndef GAME_MULTIPLAY_MAIN_H
#define GAME_MULTIPLAY_MAIN_H

#include "engine/functions.h"
#include "game/multiplay.h"

extern "C" {
void CalcItemLevel(void);
void StopBlockManager(void);
void func_02083fb8(void); // thumb
void func_02062fcc(void);
void SoundInit(void);
}

// C++ linkage (mangled in symbols.txt)
void Encounter(void);
void ShikakeMove(void);
int warp_check(void);
void WarpPlayer(void);
void ScrollMove(void);
void BgAnm(void);
void func_0208309c(void);
void func_0202809c(void);
s32 abs_s32(s32 value);

#endif
