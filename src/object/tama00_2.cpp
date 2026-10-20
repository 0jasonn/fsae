#include "engine/functions.h"
#include "game/stageseldecls.h"

// Tama00 actor family, second unit. Address -> name (original names from symbols.txt):
//   0x0207c898 tama00_move, 0x0207c8f8 tama00_hajiki, 0x0207c92c tama00_hajikiInit

// tama00_move, 0x0207c898. Moves the animation and checks the wall flags: 0xffff removes the actor, another value
// (a wall) starts the flick motion, zero only runs the common update.
ARM void tama00_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_0208b668(e);
    if (e->wallFlags != 0) {
        if (e->wallFlags == 0xffff) {
            PutObjWork(e);
            return;
        }
        func_02085a60(e, e->wallFlags);
        tama00_hajikiInit(e);
        func_0208af0c(e);
        return;
    }
    func_0208af0c(e);
}

// tama00_hajiki, 0x0207c8f8. Flick motion: moves, animates and removes the actor when it stops.
ARM void tama00_hajiki(Entity *e) {
    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    PutObjWork(e);
}

// tama00_hajikiInit, 0x0207c92c. Starts the flick motion with the animation of the direction.
ARM void tama00_hajikiInit(Entity *e) {
    e->action = 2;
    e->speed = 0x40;
    e->zVelocity = 0x14000;
    e->statusFlags = e->statusFlags & 0x7f;
    InitAnimationForceUpdate(e, (u8)((e->direction >> 4) + 2));
    EnqueueSFX(0x1d);
}
