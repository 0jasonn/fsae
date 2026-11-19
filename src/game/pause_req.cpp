#include "engine/functions.h"
#include "global.h"
#include "game/pause_req.h"

// 0x02053ab8 pause_req (original name): requests a pause of the given kind.

extern u8 frameCounter[0x20];

void pause_req(u8 kind) {
    frameCounter[0x11] = kind | 0x80;
    pauseState.mode = 3;
    pauseState.kind = kind;
    pauseState.count++;
}
