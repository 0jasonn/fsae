#include "engine/functions.h"
#include "global.h"
#include "engine/bg_buff.h"
#include "engine/map_state.h"
#include "actor/object/setdisp.h"
#include "actor/object/set3e.h"

// Set3e actor (module set3e). Address -> name:
//   0x0205d9d4 Set3e (original name), 0x0205d9f0 set3e_init
//   (set3e_init at 0x0205d9f0 is in scratch/agentF/nonmatching)

typedef struct Vars_Set3e {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 unk_64;
} Vars_Set3e;

extern const EntityFunc data_020d8c50[]; // state table indexed by e->action
extern const u8 data_020d8c48[];         // hitbox of the set3e actor

void Set3e(Entity *e) {
    data_020d8c50[e->action](e);
}

// Set3e actor, init (0x0205d9f0). The cell index is written x term first (see ss_3.cpp).

void set3e_init(Entity *e) {
    BG_BUFF_ *background;
    s32 cell;
    s32 dx;
    s32 dy;

    e->action = 1;
    e->unk_1b = 0xb;
    e->unk_20 = 0xe0;
    e->hitbox = data_020d8c48;
    e->spriteSettings.b6 = 2;
    e->spriteSettings.b0 = 1;
    func_0208ae30(e);
    e->speed = 0x180;
    background = (BG_BUFF_ *)GetBgBuffAdrs(e->layer);
    VARS(Vars_Set3e, e)->unk_64 = func_02083c84(e);
    dy = e->y.HALF.HI - mapState.originY;
    dx = e->x.HALF.HI - mapState.originX;
    cell = (dx >> 4) | ((dy >> 4) << 6);
    background->screen[cell] = 0x400e;
    dy = e->y.HALF.HI - mapState.originY;
    dx = e->x.HALF.HI - mapState.originX;
    cell = (dx >> 4) | ((dy >> 4) << 6);
    background->attr[cell] = 0x1d;
    InitAnimationForceUpdate(e, 0);
}

// Set3e actor, wait state (module set3e). Address -> name:
//   0x0205dad8 set3e_wait
//   (set3e_move at 0x0205dc1c is in src/object/set3e_2.cpp)

typedef struct Vars_Set3eWait {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 rewId; // first argument of RewCell
} Vars_Set3eWait;

extern const s8 data_020d8c40[]; // (dx, dy) pairs for the four directions, indexed by direction >> 2
extern const u8 pot_moveCheckTable[];

void set3e_wait(Entity *e) {
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
            cell = ((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
            RewCell(VARS(Vars_Set3eWait, e)->rewId, (u16)cell, e->layer);
            e->action = e->action + 1;
            EnqueueSFX(0x22c);
        } else {
            u16 *bg = (u16 *)GetBgBuffAdrs(e->layer);
            cell = ((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
            (bg + cell)[2] = 0x400e;
        }
        break;
    }
}

// Set3e actor, second unit (module set3e). Address -> name:
//   0x0205dc1c set3e_move

void set3e_move(Entity *e) {
    u8 code;

    if (e->speed < 0x300) {
        e->speed += 0x10;
    }
    func_020852ec(e);
    code = func_02083cdc(e);
    if (code == 0x22) {
        return;
    }
    if (code == 0x43) {
        EffectSet(e, 0, 0);
        PutObjWork(e);
        return;
    }
    EffectSet(e, 4, 0);
    PutObjWork(e);
}
