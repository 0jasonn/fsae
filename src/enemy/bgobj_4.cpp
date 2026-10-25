#include "engine/functions.h"
#include "global.h"
#include "enemy/bgobj.h"

// Functions in this file: bgobj_poscopy (0x0203e6c8).

ARM void bgobj_poscopy(Entity *e) {
    if (e->spriteSettings.b0 != 0) {
        ObjPosCopyOfs32(e, e->parent, 0, 0x10000);
        e->parent->z.HALF.HI = bgobj_poscopyTable[(e->animationState << 1) + (e->frame & 1)];
    } else {
        ObjPosCopy(e, e->parent);
    }
}
