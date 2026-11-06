#include "engine/functions.h"
#include "global.h"

// Set5e actor, init (module set5e; dispatcher Set5e is in set5e_1.cpp). Address -> name:
//   0x0205fff0 set5e_init (original name)

typedef struct ScrollOrigin_Set5e {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 scrollX;
    /* 1a */ u16 scrollY;
} ScrollOrigin_Set5e;

extern ScrollOrigin_Set5e mapState; // scroll origin of the current map

typedef struct Vars_Set5e_init {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 value; // cell value at the start
    /* 7a */ u8 unk_7a[2];
    /* 7c */ u16 *cellPtr; // points at the cell in the background buffer
} Vars_Set5e_init;

void set5e_init(Entity *e) {
    u16 *table;
    s32 cell;
    u32 base;
    Vars_Set5e_init *v = VARS(Vars_Set5e_init, e);
    e->action = 1;
    base = GetBgBuffAdrs(e->layer);
    table = (u16 *)(base + 4);
    cell = ((e->x.HALF.HI - mapState.scrollX) >> 4) |
           (((e->y.HALF.HI - mapState.scrollY) >> 4) << 6);
    v->cellPtr = table + cell;
    v->value = table[cell];
}
