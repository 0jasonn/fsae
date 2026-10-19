#ifndef WIP_E_MAP_H
#define WIP_E_MAP_H

// Map / collision-cell module (src/game/map.cpp). Callees that functions.h does not declare yet.
#include "engine/functions.h"

// Original signature RewCellOne(unsigned short, unsigned short, unsigned short), defined in map.cpp.
void RewCellOne(u16 cell, u16 x, u16 y);
// Thumb helper at 0x02083d00: returns non-0x43 when the cell at (x, y) is not the one checked by isAnkyo.
int func_02083d00(u16 x, u16 y);

#endif
