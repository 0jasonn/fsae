#include "engine/functions.h"
#include "global.h"
#include "object/protos.h"

// Set3e actor, wait state (module set3e). Address -> name:
//   0x0205dad8 set3e_wait
//   (set3e_move at 0x0205dc1c is in src/object/set3e_2.cpp)

typedef struct Vars_Set3eWait {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 rewId; // first argument of RewCell
} Vars_Set3eWait;

extern const s8 data_020d8c40[]; // (dx, dy) pairs for the four directions, indexed by direction >> 2
extern const u8 pot_moveCheckTable[];

ARM void set3e_wait(Entity *e) {
    s32 code = func_02083c84(e);
    s32 index;
    s32 x;
    s32 y;
    s32 cell;

    if (code == 0x4002) {
        return;
    }
    switch (code) {
    case 0x400f:
    case 0x4010:
    case 0x4011:
    case 0x4012:
        index = code - 0x400f;
        e->direction = index << 3;
        e->animationState = index;
        x = e->x.HALF.HI + data_020d8c40[(u8)e->direction >> 2];
        y = e->y.HALF.HI + data_020d8c40[((u8)e->direction >> 2) + 1];
        if (func_02085890(e, pot_moveCheckTable, x, y) == 0) {
            cell = ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6);
            RewCell(VARS(Vars_Set3eWait, e)->rewId, (u16)cell, e->layer);
            e->action = e->action + 1;
            EnqueueSFX(0x22c);
        } else {
            u16 *bg = (u16 *)GetBgBuffAdrs(e->layer);
            cell = ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6);
            (bg + cell)[2] = 0x400e;
        }
        break;
    }
}
