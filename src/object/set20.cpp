#include "engine/functions.h"
#include "global.h"
#include "object/set20.h"

// Set20 actor (module set20). Address -> name:
//   0x0206596c Set20 (dispatcher, was Set20)
//   0x02065988 set20_init, 0x02065a28 set20_move

// Dispatcher: runs the handler for the current action.
ARM void Set20(Entity *e) {
    set20_stateTable[e->action](e);
}

// Init: starts the animation and sound, sets the hitbox and the combat stats.
ARM void set20_init(Entity *e) {
    if ((e->layer & 0xc000) == 0) {
        func_0208ae30(e);
    }
    e->action++;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    e->statusFlags = 0x98;
    e->poseId = 0xb;
    e->unk_40 = 0x16;
    e->attackDamage = 10;
    e->attackKnockback = 0x10;
    e->hitbox = *(const void **)((const u8 *)set20_stateTable + 0x24);
    e->unk_5c = 0x7ff;
    InitAnimationForceUpdate(e, 1);
    func_02084180(e);
    EnqueueSFX(3);
}

// Updates the animation. A set flag in the frame byte removes the entity. Otherwise the hitbox follows the frame, or
// the status bit 0x80 is cleared for frames 5 and up.
ARM void set20_move(Entity *e) {
    u8 frame;

    UpdateAnimationSingleFrame(e);
    frame = e->frame;
    if (frame & 0x80) {
        func_020841b0(e);
        PutObjWork(e);
        return;
    }
    if (frame < 5) {
        e->hitbox = set20_hitboxTable[frame];
    } else {
        e->statusFlags &= 0x7f;
    }
}
