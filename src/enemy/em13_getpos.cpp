#include "engine/functions.h"
#include "enemy/em13.h"
#include "global.h"
#include "types.h"

// Functions in this file (module em13, the Wizzrobe warp position search):
//   em13_getpos (0x0203c570)

// em13_getpos(OBJ_WORK_*): picks a warp destination cell near the actor's position from em13_randomCellOffsets.
// Returns TRUE and stores the warp home (warpX/warpY) when the destination is free and the sub position is inside it;
// a blocked cell makes the actor choose a new move with nextMove, and the function returns FALSE.
ARM BOOL em13_getpos(Entity *e) {
    u16 cell;
    u16 newX;
    u16 newY;
    u16 dx;
    u16 dy;
    u32 index;

    cell = (u16)(((e->x.HALF.HI - data_0212c648.originX) >> 4) |
                 (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6));
    index = (u32)Random() & 0x1f;
    cell = (u16)(em13_randomCellOffsets[index] + cell);
    if (func_02083d4c(cell, 0x4000) != 0) {
        goto nomove;
    }
    if (func_02083d4c(cell, 0x8000) != 0) {
        goto nomove;
    }
    newX = (u16)(((cell & 0x3f) << 4) + 8 + data_0212c648.originX);
    newY = (u16)(((cell & 0xfc0) >> 2) + 8 + data_0212c648.originY);
    if (V(e)->subX == 0 && V(e)->subY == 0) {
        V(e)->warpX = newX;
        V(e)->warpY = newY;
        return TRUE;
    }
    dx = (u16)(newX - V(e)->cellX);
    if (V(e)->subX < dx) {
        goto falseret;
    }
    dy = (u16)(newY - V(e)->cellY);
    if (V(e)->subY < dy) {
        goto falseret;
    }
    V(e)->warpX = newX;
    V(e)->warpY = newY;
    return TRUE;
nomove:
    nextMove(e);
falseret:
    return FALSE;
}
