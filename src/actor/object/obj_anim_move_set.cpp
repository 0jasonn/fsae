#include "engine/functions.h"
#include "global.h"

// 0x0205069c ObjAnimMoveSet (original name): starts a move animation of the entity towards bounds[0], bounds[1];
// flags (0 counts as 1) is the step divisor.

typedef struct Vars_AnimMove {
    /* 00 */ u8 unk_00[0x76];
    /* 76 */ u8 phase;
    /* 77 */ u8 divisor;
    /* 78 */ s16 startX;
    /* 7a */ s16 startY;
    /* 7c */ u16 boundX;
    /* 7e */ u16 boundY;
} Vars_AnimMove;

void ObjAnimMoveSet(Entity *e, const u16 *bounds, u8 flags) {
    if (flags == 0) {
        flags = 1;
    }
    VARS(Vars_AnimMove, e)->phase = 0;
    VARS(Vars_AnimMove, e)->divisor = flags;
    VARS(Vars_AnimMove, e)->startX = e->x.HALF.HI;
    VARS(Vars_AnimMove, e)->startY = e->y.HALF.HI;
    VARS(Vars_AnimMove, e)->boundX = bounds[0];
    VARS(Vars_AnimMove, e)->boundY = bounds[1];
}
