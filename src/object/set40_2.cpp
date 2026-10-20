#include "engine/functions.h"
#include "global.h"
#include "object/set40.h"

// Set40 family (module set40), 0x0206bec4 .. 0x0206bf28.
// Address -> name: 0x0206bec4 set40_move, 0x0206befc set40_lift

ARM void set40_move(Entity *e) {
    func_02089524(e);
    if (VARS(Vars_Set40, e)->value == 0) {
        return;
    }
    e->direction = e->type << 3;
    MoveDir(e);
    nemoto_setdist(e);
}

ARM void set40_lift(Entity *e) {
    ObjHippariCheck(e);
    set40LiftTable[e->subAction - 5](e);
}
