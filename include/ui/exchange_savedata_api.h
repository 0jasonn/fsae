#ifndef GAME_EXCHANGE_SAVEDATA_API_H
#define GAME_EXCHANGE_SAVEDATA_API_H

// Functions defined in src/game/exchange_savedata*.cpp.

#include "engine/entity.h"

extern "C" {
void exchange_savedata(void);
BOOL is_exchange_savedata_end(void);
void leaveLobby(void);
}

#endif
