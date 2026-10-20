#include "engine/functions.h"
#include "global.h"

// Set2f actor, second unit (module set2f). Address -> name:
//   0x0205afac set2f_move (original name)
//   0x0205b024 rewlever (original name)

typedef struct Vars_Set2f {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u8 triggered; // set once set2f_move has flipped the actor
} Vars_Set2f;

// data_0212c648 as read by rewlever: grid origin of the map cells.
typedef struct Set2fGridOrigin {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 originX;
    /* 1a */ u16 originY;
} Set2fGridOrigin;

extern u32 em12_typeMasks[];
extern const u32 flagBits[]; // flagBits, indexed by e->type
extern Set2fGridOrigin data_0212c648;

void rewlever(Entity *e);

ARM void set2f_move(Entity *e) {
    if ((e->contactFlags & 0x80) == 0) {
        return;
    }
    if (VARS(Vars_Set2f, e)->triggered != 0) {
        return;
    }
    VARS(Vars_Set2f, e)->triggered = 1;
    e->type2 = e->type2 ^ 1;
    e->iframes = 0xe8;
    rewlever(e);
    em12_typeMasks[e->areaIndex] ^= flagBits[e->type];
    func_02085f98(e, 0x17);
}

ARM void rewlever(Entity *e) {
    if (e->type2 != 0) {
        RewCell(0x14d, ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6), e->layer);
    } else {
        RewCell(0x14c, ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6), e->layer);
    }
}
