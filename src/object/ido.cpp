#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Ido movement helpers (module ido). Address -> name:
//   0x02064e74 ido_up, 0x02064ea0 ido_right, 0x02064ecc ido_down, 0x02064ef8 ido_left (original names)

typedef struct Vars_Ido {
    /* 00 */ u8 unk_00[0x74];
    /* 74 */ u16 targetPos; // position the actor is moving to along the axis
} Vars_Ido;

ARM void ido_up(Entity *e) {
    ido_yukaMove(e);
    if ((s32)VARS(Vars_Ido, e)->targetPos < (s32)e->y.HALF.HI) {
        return;
    }
    e->y.HALF.HI = VARS(Vars_Ido, e)->targetPos;
    ido_getNextInfo(e);
}

ARM void ido_right(Entity *e) {
    ido_yukaMove(e);
    if ((s32)VARS(Vars_Ido, e)->targetPos > (s32)e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = VARS(Vars_Ido, e)->targetPos;
    ido_getNextInfo(e);
}

ARM void ido_down(Entity *e) {
    ido_yukaMove(e);
    if ((s32)VARS(Vars_Ido, e)->targetPos > (s32)e->y.HALF.HI) {
        return;
    }
    e->y.HALF.HI = VARS(Vars_Ido, e)->targetPos;
    ido_getNextInfo(e);
}

ARM void ido_left(Entity *e) {
    ido_yukaMove(e);
    if ((s32)VARS(Vars_Ido, e)->targetPos < (s32)e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = VARS(Vars_Ido, e)->targetPos;
    ido_getNextInfo(e);
}
