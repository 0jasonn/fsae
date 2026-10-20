#include "engine/functions.h"
#include "global.h"
#include "object/heart_lift.h"

// stick family (module stick), 0x0206c068 .. 0x0206c0b0.
// Address -> name: 0x0206c068 stick_init (stick_move, 0x0206c0b0, is parked in scratch/agentA/nonmatching)

// Parent fields read by stick_move (file-local overlay on the parent entity).
typedef struct Vars_StickParent {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 stickPos; // encoded position: (stickPos - 8) & 7 is the sub-cell offset, (stickPos - 8) >> 4 the anim
} Vars_StickParent;

ARM void stick_init(Entity *e) {
    e->action = 1;
    e->unk_5e.b0 = 0;
    e->y.HALF.HI -= 1;
    InitAnimationForceUpdate(e, e->parent->type + 8);
    func_0208ae78(e);
}
