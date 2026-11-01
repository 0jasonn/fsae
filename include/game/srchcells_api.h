#ifndef GAME_SRCHCELLS_API_H
#define GAME_SRCHCELLS_API_H

// Functions defined in src/game/srchcells*.cpp.

#include "engine/entity.h"

extern "C" {
u16 *srchCells(u16 start, u16 width, u16 height);
}

#endif
