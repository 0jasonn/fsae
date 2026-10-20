#include "engine/functions.h"
#include "object/tama_decls.h"

// Tama01 actor family. Address -> name (original names from symbols.txt):
//   0x0207df5c Tama01, 0x0207df98 tama01_init, 0x0207dfd8 tama01_move0, 0x0207e04c tama01_move1

// Tama01, 0x0207df5c. A contact with bit 7 set and a kind up to 7 removes the actor; otherwise runs the action.
ARM void Tama01(Entity *e) {
    if ((e->contactFlags & 0x80) != 0 && (e->contactFlags & 0x7f) <= 7) {
        PutObjWork(e);
        return;
    }
    data_020dcb88[e->action](e);
}

// tama01_init, 0x0207df98. Advances the action, sets the timer to 8 and the first animation.
ARM void tama01_init(Entity *e) {
    e->action = e->action + 1;
    e->timer = 8;
    e->spriteSettings.b0 = 1;
    e->hitbox = data_020dcb74;
    InitAnimationForceUpdate(e, 0);
}

// tama01_move0, 0x0207dfd8. Counts the timer down and advances the action at zero. Every second frame toggles the
// sprite bit b16, then moves the actor.
ARM void tama01_move0(Entity *e) {
    e->timer = e->timer - 1;
    if (e->timer == 0) {
        e->action = e->action + 1;
    }
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 1) != 0) {
        e->frame = 0;
        e->spriteSettings.b16 = e->spriteSettings.b16 ^ 1;
    }
    MoveDir(e);
    func_0208af0c(e);
}

// tama01_move1, 0x0207e04c. Like tama01_move0 without the timer; removes the actor when a wall was hit.
ARM void tama01_move1(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 1) != 0) {
        e->frame = 0;
        e->spriteSettings.b16 = e->spriteSettings.b16 ^ 1;
    }
    func_0208b668(e);
    func_0208af0c(e);
    if (e->wallFlags != 0) {
        PutObjWork(e);
    }
}
