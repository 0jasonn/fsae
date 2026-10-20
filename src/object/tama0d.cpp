#include "engine/functions.h"
#include "game/stageseldecls.h"

// Tama0d actor family, first unit. Address -> name (original names from symbols.txt):
//   0x0207cea8 Tama0d, 0x0207cf44 tama0d_init

// Tama0d, 0x0207cea8. A contact flagged with bit 7 (and at least 0x84) releases a random child and removes the
// actor; otherwise runs the action of the table.
ARM void Tama0d(Entity *e) {
    if ((e->contactFlags & 0x80) != 0 && e->contactFlags >= 0x84) {
        Entity *child;
        u8 kind = data_020dcad9[Random() & 0xf];
        if (kind != 0xff) {
            child = GetSetWork(0, kind, 1);
            if (child != 0) {
                ObjPosCopy(e, child);
            }
        }
        child = GetSetWork(0xf, 6, 0);
        if (child != 0) {
            ObjPosCopy(e, child);
        }
        PutObjWork(e);
    } else {
        data_020dcaec[e->action](e);
    }
}

// tama0d_init, 0x0207cf44. Starts the actor with a random speed from the table and the first animation.
ARM void tama0d_init(Entity *e) {
    u32 settings;
    e->action = 1;
    settings = *(u32 *)&e->spriteSettings;
    e->timer = 8;
    e->unk_2e = 3;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b4 = 1;
    e->zVelocity = 0x30000;
    e->speed = data_020dcac8[Random() & 3];
    e->unk_5e.b0 = 3;
    e->hitbox = data_020dcad0;
    InitAnimationForceUpdate(e, 0xa);
}

// tama0d_move, 0x0207cfcc. Counts the timer down (at zero the statusFlags bit 7 is set); when it stops rising it
// starts the falling action.
ARM void tama0d_move(Entity *e) {
    s32 timer = e->timer - 1;
    e->timer = timer;
    if ((timer & 0xff) == 0) {
        e->statusFlags = e->statusFlags | 0x80;
    }
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    e->action = 2;
    e->zVelocity = 0x1c000;
    e->statusFlags = e->statusFlags | 0x10;
}

// tama0d_move2, 0x0207d034. Falls to the next action when the gravity update reports the ground.
ARM void tama0d_move2(Entity *e) {
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (UpdateGravity(e, 0x1800) == 0) {
        e->action = 3;
        e->zVelocity = 0x12000;
    }
}

// tama0d_move3, 0x0207d06c. Falls to the last action and sets the unk_5c value.
ARM void tama0d_move3(Entity *e) {
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    e->action = 4;
    e->zVelocity = 0xe000;
    e->unk_5c = 0x21aa;
}

// tama0d_move4, 0x0207d0b4. Takes the animation bit from frameCounter and removes the actor when it lands.
ARM void tama0d_move4(Entity *e) {
    e->spriteSettings.b0 = *(u16 *)frameCounter & 1;
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    PutObjWork(e);
}
