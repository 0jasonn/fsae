#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/set23.h"

// Set23 actor, second unit (module set23). Address -> name:
//   0x020662b8 set23_wait, 0x020662e4 set23_wait2move, 0x02066330 set23_move, 0x020663ac set23_move2close,
//   0x02066424 set23_close, 0x02066488 set23_close2open

// Waits for the type bits to show up in the area mask, then advances.
ARM void set23_wait(Entity *e) {
    if (VARS(Vars_Set23, e)->typeBits == (VARS(Vars_Set23, e)->typeBits & em12_typeMasks[e->areaIndex])) {
        e->action++;
    }
}

// Waits for the animation to end (frame bit 0x80), then switches to the opening state and sets the status flag.
ARM void set23_wait2move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action++;
    e->statusFlags |= 0x80;
    e->animationState = e->animationState - 4;
    InitAnimationForceUpdate(e, e->animationState);
}

// Moves while the contacted entity keeps the same direction. Sets the area mask bit of the type and plays a sound.
ARM void set23_move(Entity *e) {
    if (e->contactFlags != 0x95) {
        return;
    }
    if (((((e->contactedEntity->direction + 4) & 0x18) >> 3)) != (e->animationState & 3)) {
        return;
    }
    e->action++;
    e->statusFlags &= 0x7f;
    em12_typeMasks[e->areaIndex] |= flagBits[e->type2];
    EnqueueSFX(0x17);
}

// Animation step of the closing move. The timer comes from the wireless mode, or from the timer of the entity.
ARM void set23_move2close(Entity *e) {
    u8 anim;

    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action++;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        VARS(Vars_Set23, e)->closeTimer = e->timer * 2;
    } else {
        if (e->timer != 0 && e->timer < 60) {
            VARS(Vars_Set23, e)->closeTimer = 0xb4;
        } else {
            VARS(Vars_Set23, e)->closeTimer = e->timer * 3;
        }
    }
    anim = e->animationState + 4;
    InitAnimationForceUpdate(e, anim);
}

// Counts the close timer down, then clears the area mask bit of the type and advances.
ARM void set23_close(Entity *e) {
    if (e->timer == 0) {
        return;
    }
    if (--VARS(Vars_Set23, e)->closeTimer != 0) {
        return;
    }
    e->action++;
    em12_typeMasks[e->areaIndex] &= ~flagBits[e->type2];
}

// Waits for the animation to end, then goes back one state and sets the status flag.
ARM void set23_close2open(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    e->action -= 3;
    e->statusFlags |= 0x80;
    InitAnimationForceUpdate(e, e->animationState);
}
