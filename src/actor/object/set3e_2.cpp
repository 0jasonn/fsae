#include "engine/functions.h"
#include "global.h"
#include "actor/object/cellcalls.h"

// Set3e actor, init (0x0205d9f0). The cell index is written x term first (see ss_3.cpp).
typedef struct Vars_Set3e {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 unk_64;
} Vars_Set3e;

extern const u8 data_020d8c48[];         // hitbox of the set3e actor

void set3e_init(Entity *e) {
    u16 *background;
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
    background = (u16 *)GetBgBuffAdrs(e->layer);
    VARS(Vars_Set3e, e)->unk_64 = func_02083c84(e);
    dy = e->y.HALF.HI - mapState.originY;
    dx = e->x.HALF.HI - mapState.originX;
    cell = (dx >> 4) | ((dy >> 4) << 6);
    background[cell + 2] = 0x400e;
    dy = e->y.HALF.HI - mapState.originY;
    dx = e->x.HALF.HI - mapState.originX;
    cell = (dx >> 4) | ((dy >> 4) << 6);
    *(u8 *)((u32)background + 0x2004 + cell) = 0x1d;
    InitAnimationForceUpdate(e, 0);
}
