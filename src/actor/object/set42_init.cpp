#include "engine/functions.h"
#include "actor/object/set42_actions.h"

// Set42 actor (module set42). Address -> name:
//   0x0206c720 set42_init (original name)

extern s16 scrollArgs[3]; // scale x, scale y, angle for ObjAffineSet2

// Starts the actor: scaled up (0x200) and lifted, with the cg of the effect loaded; type 0 starts its special
// animation and sound, the others start animation 0.
void set42_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->action++;
    e->spriteSettings.b14 = 0;
    e->unk_5e.b0 = 0;
    e->spriteSettings.b30 = 0;
    e->timer = 0xfc;
    func_02085cf8(e);
    scrollArgs[1] = 0x200;
    scrollArgs[0] = scrollArgs[1];
    scrollArgs[2] = 0;
    ObjAffineSet2((KnifeObjAffineSrcData *)scrollArgs, e);
    e->z.HALF.HI = 0x10;
    CgLoad(0x1b);
    if (e->type == 0) {
        func_020859a0(e, 0, 3);
        SoundReq(0x19);
    } else {
        InitAnimationForceUpdate(e, 0);
    }
}
