#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em14.h"

// Actor fields of em14 past the shared Entity fields.
typedef struct Vars_Em14GetPos {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s16 savedX; // x of the position when it was placed
    /* 72 */ s16 savedY; // y of the position when it was placed
} Vars_Em14GetPos;

extern const s16 em14_targetOffsets[]; // (x, y) offset pairs around the parent, picked from the facing direction

// em14_getpos_03cbe4 (0x0203cbe4, original getpos): turns the actor a quarter turn either way from its parent's
// direction and places it next to the parent. Returns FALSE when the new spot is blocked (flag between 1 and 0x1f).
BOOL em14_getpos_03cbe4(Entity *e) {
    const s16 *offset;
    u32 blockFlag;

    e->direction = ((e->child->animationState + ((s32)(Random() % 3) - 1) * 2) & 6) << 2;
    e->animationState = e->direction >> 3;
    offset = &em14_targetOffsets[(Random() & 2) + (e->direction >> 1)];
    e->x.HALF.HI = e->child->x.HALF.HI + offset[0];
    e->y.HALF.HI = e->child->y.HALF.HI + offset[1];
    e->layer = e->child->layer;
    func_0208ae30(e);
    blockFlag = func_02083d28(e);
    if (blockFlag != 0 && blockFlag < 0x20) {
        return FALSE;
    }
    VARS(Vars_Em14GetPos, e)->savedX = e->x.HALF.HI;
    VARS(Vars_Em14GetPos, e)->savedY = e->y.HALF.HI;
    InitAnimationForceUpdate(e, e->animationState);
    return TRUE;
}
