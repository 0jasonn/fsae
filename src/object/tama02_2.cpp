#include "engine/functions.h"
#include "object/tama02.h"

// tama02 family, address -> name (original names from symbols.txt):
//   0x0207e51c tama02_tobashi, 0x0207e560 tobashiInit

// tama02_tobashi, 0x0207e51c. Clears the health and gives the partner invincibility frames when the sideways move
// ends without a collision; otherwise it returns early.
ARM void tama02_tobashi(Entity *e) {
    func_0208b644(e);
    if (UpdateGravity(e, 0x2800) != 0) {
        return;
    }
    e->health = 0;
    VARS(Vars_Tama02, e)->partner->iframes = 0xe2;
    ObjPosCopy(e, VARS(Vars_Tama02, e)->partner);
}

// tobashiInit, 0x0207e560. Turns the actor to the partner's side, sets the arc speed from the parent's kind and
// starts the falling state (action 2).
ARM void tobashiInit(Entity *e) {
    s32 threshold;
    e->action = 2;
    e->direction = (u8)(((s32)(u8)(e->direction - 0x40)) >> 3);
    threshold = (s32)data_020dcb94[VARS(Vars_Tama02Parent, e->parent)->parentKind] + 4;
    if (threshold > e->z.HALF.HI) {
        e->type2 = 1;
        e->zVelocity = 0x1c000;
        e->speed = 0x180;
    } else {
        e->zVelocity = 0xc000;
        e->speed = 0x200;
    }
}
