#ifndef ENGINE_MAKE_MAP_SCREEN_H
#define ENGINE_MAKE_MAP_SCREEN_H

#include "engine/bg_buff.h"

// MakeMapScreen has no C++ name in the original (plain symbol); src/engine/scr_4.cpp declares it as (const void *, void *).
extern "C" {
void MakeMapScreen(u16 *map, BG_BUFF_ *buffer);
}

#endif
