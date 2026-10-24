#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/lobby.h"

// Functions in this file (no original names, provisional name):
//   lobby_updateNone (lobby_updateNone)

// lobby_updateNone() (0x020b3ea0, provisional name): update step without work, returns 0
extern "C" s32 lobby_updateNone(void);
ARM s32 lobby_updateNone(void) {
    return 0;
}
