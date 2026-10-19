#ifndef WIP_C_COMMON_H
#define WIP_C_COMMON_H

#include "types.h"

// Defined in src/wip/E/map.cpp (original signature RewCellOne(unsigned short, unsigned short, unsigned short))
void RewCellOne(u16 cell, u16 x, u16 y);

// Defined in src/engine/cell.cpp (original signature SearchCellTbl(unsigned short const*, unsigned short))
int SearchCellTbl(const u16 *table, u16 key);

#endif
