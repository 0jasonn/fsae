#ifndef GAME_PENDING_PTR_API_H
#define GAME_PENDING_PTR_API_H

// Functions defined in src/game/pending_ptr*.cpp.

#include "engine/entity.h"

extern "C" {
void *Knife_Message_getPendingPtr(void);
}

#endif
