#ifndef WIP_RANDOMBLOCK_H
#define WIP_RANDOMBLOCK_H

#include "engine/functions.h"

void frame_block_set(u16 x, u16 y, u16 cell, u8 kind); // 0x0204e634 (game/blockset.cpp), not in functions.h yet
void RandomBlockSet(const u8 *list, u8 param);         // 0x0204e690, original RandomBlockSet(unsigned char const*, unsigned char)

#endif
