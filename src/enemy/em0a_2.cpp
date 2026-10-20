#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em00.h"

// Functions in this file (actor em0a, provisional names from their behaviour):
//   em0a_jump -> em0a_jump, em0a_wait -> em0a_wait

// Jump: gravity, and when the actor is falling close to the floor it starts the next state with 30 frames.
ARM void em0a_jump(Entity *e) {
    UpdateGravity(e, 0x2800);
    if (e->zVelocity >= 0) {
        return;
    }
    if (e->z.HALF.HI <= -8) {
        return;
    }
    e->action += 1;
    e->timer = 0x1e;
    e->statusFlags |= 0x80;
}

// Wait: counts the timer, then the subtimer with the frame bit; at the end the direction is set and the smoke starts.
ARM void em0a_wait(Entity *e) {
    if (e->timer != 0) {
        e->timer -= 1;
        e->subtimer = 0xc;
        return;
    }
    UpdateAnimationSingleFrame(e);
    e->subtimer -= e->frame & 1;
    if (e->subtimer != 0) {
        return;
    }
    e->action += 1;
    if (e->child != 0) {
        e->direction = GetFacingDirection(e, e->child);
    } else {
        e->direction = Random() & 0x1f;
    }
    KemuriSet(e);
}

// Move: animation and the wall check; a hit on a wall copies the position and plays the sound, otherwise the map cell
// under the actor decides whether the actor keeps moving.
ARM void em0a_move(Entity *e) {
    Entity *work;
    u16 cell;
    u16 kind;

    UpdateAnimationSingleFrame(e);
    func_020847c8(e);
    if (e->wallFlags != 0) {
        work = GetSetWork(0xf, 5, 0x40);
        if (work != 0) {
            ObjPosCopy(e, work);
            func_02085f98(e, 0x221);
        }
        PutObjWork(e);
        return;
    }
    if ((e->layer & 0x4000) == 0) {
        return;
    }
    s16 posY;
    s16 posX;

    posY = e->y.HALF.HI;
    posX = e->x.HALF.HI;
    cell = (u16)((posX >> 4) | ((posY >> 4) << 6));
    kind = (u16)(func_02083e54(func_02083ca8(cell, e->layer)) + 0x3b8 + 0xfc00);
    if (kind > 1) {
        return;
    }
    work = GetSetWork(0xf, 5, 0x40);
    if (work != 0) {
        ObjPosCopy(e, work);
        func_02085f98(e, 0x221);
    }
    PutObjWork(e);
}
