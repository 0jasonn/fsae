#ifndef UI_LOBBY_COLOR_API_H
#define UI_LOBBY_COLOR_API_H

// Functions defined in src/game/lobby_color*.cpp.

#include "engine/entity.h"

extern "C" {
BOOL isFinishedColorChoiceAllPlayers(void);
BOOL isSpaceColorSlot(s32 slot);
}

#endif
