#include "engine/functions.h"
#include "global.h"
#include "actor/object/set2f.h"

// Set2f actor, second unit (module set2f). Address -> name:
//   0x0205afac set2f_move (original name)
//   0x0205b024 rewlever (original name)

extern u32 em12_typeMasks[];
extern const u32 flagBits[]; // flagBits, indexed by e->type
extern Set2fGridOrigin data_0212c648;

void rewlever(Entity *e);

void set2f_move(Entity *e) {
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

void rewlever(Entity *e) {
    if (e->type2 != 0) {
        RewCell(0x14d, ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6), e->layer);
    } else {
        RewCell(0x14c, ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6), e->layer);
    }
}
