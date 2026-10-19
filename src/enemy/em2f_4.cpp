#include "engine/functions.h"
#include "enemy/em2f.h"
#include "global.h"

ARM void getStormMoveInfo(Entity *e) {
    V(e)->pathCursor = em2f_stormPaths[Random() & 1];
    V(e)->targetX = *V(e)->pathCursor++;
    V(e)->targetY = *V(e)->pathCursor++;
    e->direction = *V(e)->pathCursor++;
    V(e)->pathWait = 0x80;
}

