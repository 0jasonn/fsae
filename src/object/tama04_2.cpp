#include "engine/functions.h"
#include "object/tama04_2.h"

// tama04 family, address -> name (original names from symbols.txt):
//   0x0207e650 tama04_init, 0x0207e6a8 tama04_move, 0x0207e700 tama04_hajiki, 0x0207e734 tama04_hajikiInit

// tama04_init, 0x0207e650. Moves to the next action, lowers the actor by 2, sets the hitbox and the flick state.
ARM void tama04_init(Entity *e) {
    e->action = e->action + 1;
    e->z.HALF.HI = e->z.HALF.HI - 2;
    e->unk_2e = 2;
    e->unk_23 = 0;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b4 = 1;
    e->hitbox = data_020dcc80;
    InitAnimationForceUpdate(e, 0);
}

// tama04_move, 0x0207e6a8. Animates the actor; when it is blocked it runs the blocked handler, when it hits a wall it
// starts the flick, and it is removed when no wall was hit.
ARM void tama04_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (func_0208b668(e) == 0) {
        if (e->wallFlags == 0xffff) {
            PutObjWork(e);
        } else {
            func_02085a60(e, e->wallFlags);
            tama04_hajikiInit(e);
        }
    } else {
        func_0208af0c(e);
    }
}

// tama04_hajiki, 0x0207e700. Moves the flying actor with gravity and removes it when it lands.
ARM void tama04_hajiki(Entity *e) {
    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    PutObjWork(e);
}

// tama04_hajikiInit, 0x0207e734. Starts the flick: action 2 with speed 0x40 and a rising z velocity; plays SFX 0x233.
ARM void tama04_hajikiInit(Entity *e) {
    e->action = 2;
    e->speed = 0x40;
    e->zVelocity = 0x14000;
    e->statusFlags = e->statusFlags & 0x7f;
    EnqueueSFX(0x233);
}
