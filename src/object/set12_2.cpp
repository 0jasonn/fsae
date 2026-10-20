#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"
#include "object/set12.h"

// Set12 actor, second unit (module set12). Address -> name:
//   0x020639a8 set12_move, 0x02063ab0 set12_vanish, 0x02063b10 set12_appear, 0x02063b6c set12_wait (original names)

ARM void set12_move(Entity *e) {
    u8 slot;

    if (e->type & 0x80) {
        if (VARS(Vars_Set12, e)->isPresent == 0) {
            if (!(e->x.HALF.HI == VARS(Vars_Set12, e)->homeX && e->y.HALF.HI == VARS(Vars_Set12, e)->homeY)) {
                if (flagBits[e->type & 0x1f] & em12_typeMasks[e->areaIndex]) {
                    if ((u8)(VARS(Vars_Set12, e)->requestBits & 0xf) == 0) {
                        e->action = e->action + 1;
                        e->timer = 0x2d;
                        VARS(Vars_Set12, e)->isPresent = 1;
                        InitAnimationForceUpdate(e, 1);
                        return;
                    }
                }
            }
        }
    }

    slot = (VARS(Vars_Set12, e)->requestBits & 0xf0) >> 4;
    e->direction = set12_directionTable[slot];
    if (e->direction != 0xff) {
        rc_yukaMove(e);
    }
    if (slot != VARS(Vars_Set12, e)->lastSlot && (slot & (slot ^ VARS(Vars_Set12, e)->lastSlot)) != 0) {
        EnqueueSFX(0x12);
    }
    VARS(Vars_Set12, e)->lastSlot = slot;
    InitAnimationForceUpdate(e, slot + 1);
}

ARM void set12_vanish(Entity *e) {
    e->timer = e->timer - 1;
    if (e->timer != 0) {
        e->spriteSettings.b0 = e->spriteSettings.b0 ^ 1;
        return;
    }
    e->timer = 0x2d;
    e->action = e->action + 1;
    e->x.HALF.HI = VARS(Vars_Set12, e)->homeX;
    e->y.HALF.HI = VARS(Vars_Set12, e)->homeY;
}

ARM void set12_appear(Entity *e) {
    e->timer = e->timer - 1;
    if (e->timer != 0) {
        e->spriteSettings.b0 = e->spriteSettings.b0 ^ 1;
        return;
    }
    e->action = 1;
    VARS(Vars_Set12, e)->isPresent = 0;
    e->spriteSettings.b0 = 1;
}

ARM void set12_wait(Entity *e) {
    u8 nextAction;

    if (flagBits[e->type & 0x1f] & em12_typeMasks[e->areaIndex]) {
        nextAction = e->action - 1;
        e->timer = 0x2d;
        e->action = nextAction;
    }
}
