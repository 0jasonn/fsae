#ifndef GAME_LOBBY_PTRARRAY_API_H
#define GAME_LOBBY_PTRARRAY_API_H

// Functions defined in src/game/lobby_ptrarray*.cpp.

#include "engine/entity.h"

extern "C" {
void **lobby_allocPtrArray(void *owner, s32 count);
}

#endif
