#include "engine/functions.h"
#include "actor/object/objdecls.h"

extern s16 scrollArgs[3]; // scale x, scale y, angle for ObjAffineSet2

// set6b_wait, 0x02061330. Animates; when the timer runs out reloads it with 0xb4 and moves on, otherwise scales the
// sprite by 0x100 + timer, lifts it by timer / 16 and counts the timer down by 4.
void set6b_wait(Entity *e) {
    if (e->type == 0) {
        func_02085934(e, 3);
    } else {
        UpdateAnimationSingleFrame(e);
    }
    if (e->timer != 0) {
        scrollArgs[1] = e->timer + 0x100;
        scrollArgs[0] = scrollArgs[1];
        scrollArgs[2] = 0;
        ObjAffineSet2((KnifeObjAffineSrcData *)scrollArgs, e);
        e->z.HALF.HI = e->timer >> 4;
        e->timer -= 4;
    } else {
        e->action++;
        e->timer = 0xb4;
    }
}
