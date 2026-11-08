#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/ido_3.h"
#include "actor/object/ido_move.h"

#define IDO_MOVE_PLAYER(bit, idx, dir)                                                              \
    if ((mask & (bit)) && ido_yukaPlMoveCheck(&playerWork[idx])) {                               \
        func_020852f8(playerWork[idx].entity, dist, dir);                                        \
    }

void ido_yukaMove(Entity *e) {
    Vars_IdoMove *v;
    u8 dir;
    u32 dist;
    u32 i;
    u8 mask;
    v = VARS(Vars_IdoMove, e);
    dist = 0;
    mask = v->moveCheckMask & 0xf;
    v->prevX = e->x.HALF.HI;
    v->prevY = e->y.HALF.HI;
    dir = e->direction >> 3;
    switch (dir) {
    case 0:
        MoveDir(e);
        dist = ((u32)(v->prevY - e->y.HALF.HI) << 24) >> 16;
        if (dist != 0) {
            IDO_MOVE_PLAYER(1, 0, 0)
            IDO_MOVE_PLAYER(2, 1, 0)
            IDO_MOVE_PLAYER(4, 2, 0)
            IDO_MOVE_PLAYER(8, 3, 0)
        }
        break;
    case 1:
        MoveDir(e);
        dist = ((u32)(e->x.HALF.HI - v->prevX) << 24) >> 16;
        if (dist != 0) {
            IDO_MOVE_PLAYER(1, 0, 8)
            IDO_MOVE_PLAYER(2, 1, 8)
            IDO_MOVE_PLAYER(4, 2, 8)
            IDO_MOVE_PLAYER(8, 3, 8)
        }
        break;
    case 2:
        MoveDir(e);
        dist = ((u32)(e->y.HALF.HI - v->prevY) << 24) >> 16;
        if (dist != 0) {
            IDO_MOVE_PLAYER(1, 0, 0x10)
            IDO_MOVE_PLAYER(2, 1, 0x10)
            IDO_MOVE_PLAYER(4, 2, 0x10)
            IDO_MOVE_PLAYER(8, 3, 0x10)
        }
        break;
    case 3:
        MoveDir(e);
        dist = ((u32)(v->prevX - e->x.HALF.HI) << 24) >> 16;
        if (dist != 0) {
            IDO_MOVE_PLAYER(1, 0, 0x18)
            IDO_MOVE_PLAYER(2, 1, 0x18)
            IDO_MOVE_PLAYER(4, 2, 0x18)
            IDO_MOVE_PLAYER(8, 3, 0x18)
        }
        break;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        return;
    }
    if (mask == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (mask & (1 << i)) {
            if (ido_yukaPlMoveCheck(&playerWork[i]) == 0) {
                mask &= (u8)~(1 << i);
            }
        }
    }
    Knife_Single_SinglePlay_SetObjMoveReqFlag(Knife_Single_SinglePlay_GetInstance(), e, mask, dist, (dir & 3) << 3);
}
