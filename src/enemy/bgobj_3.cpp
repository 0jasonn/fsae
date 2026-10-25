#include "engine/functions.h"
#include "global.h"
#include "enemy/bgobj.h"

// Functions in this file: bgobj_lift_throw (0x0203e6a0), bgobj_lift_nop3 (0x0203e6c4, empty state 3).

ARM void bgobj_lift_throw(Entity *e) {
    if (e->z.HALF.HI == 0) {
        effectset(e);
        PutObjWork(e);
    }
}

ARM void bgobj_lift_nop3(Entity *e) {
}
