#ifndef GAME_MULTIPLAY_MAIN_H
#define GAME_MULTIPLAY_MAIN_H

#include "engine/functions.h"
#include "game/multiplay.h"
#include "knife/comm/comm.h"

extern "C" {
void func_02083fb8(void); // thumb
void func_02062fcc(void);
void SoundInit(void);
}

// C++ linkage (mangled in symbols.txt)
void Encounter(void);
void ShikakeMove(void);
int warp_check(void);
void WarpPlayer(void);

// CalcItemLevel has C++ linkage (original CalcItemLevel()), 0x0207c26c.
void CalcItemLevel(void);

// StopBlockManager has C++ linkage (original StopBlockManager()), 0x0204e958.
void StopBlockManager(void);

#endif
