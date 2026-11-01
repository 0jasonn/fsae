#ifndef GAME_DOORSEL_API_H
#define GAME_DOORSEL_API_H

// Functions defined in src/game/doorsel*.cpp.

#include "engine/entity.h"

extern "C" {
void DoorSelTask(void);
void doorsel_sync(void);
}

#endif
