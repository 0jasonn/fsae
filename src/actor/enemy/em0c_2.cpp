#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "actor/enemy/em00.h"
#include "game/em0c_3.h"

// Functions in this file (actor em0c, provisional names from their behaviour):
//   em0c_stop -> em0c_stop, em0c_wait -> em0c_wait

// Stop: when the flags at 0x74 are all inside the mask of the area, the action becomes 2.
void em0c_stop(Entity *e) {
    u32 flags;
    u32 masked;

    flags = *(u32 *)((u8 *)e + 0x74);
    masked = flags & em12_typeMasks[e->areaIndex];
    if (flags == masked) {
        e->action = 2;
    }
}

// Wait: counts the subtimer down (action 3 at zero). Then the type decides: with bit 1 the object is put away when the
// mask of the area is inside the flags at 0x78; with type 1 the action returns to 1 when the flags at 0x74 leave the mask.
void em0c_wait(Entity *e) {
    u32 flags;
    u32 masked;

    e->subtimer -= 1;
    if (e->subtimer == 0) {
        e->action = 3;
    }
    if ((e->type & 2) != 0) {
        flags = *(u32 *)((u8 *)e + 0x78);
        masked = flags & em12_typeMasks[e->areaIndex];
        if (flags != masked) {
            return;
        }
        PutObjWork(e);
        return;
    }
    if (e->type != 1) {
        return;
    }
    flags = *(u32 *)((u8 *)e + 0x74);
    masked = flags & em12_typeMasks[e->areaIndex];
    if (flags != masked) {
        e->action = 1;
    }
}

// em0c_shoot(e) (0x0202c80c): when the target player is inside the sensor box of the actor and the player area check
// fails, the actor fires a shot (EmGetTama) in the direction it faces (or at the target when bit 0x20 of the direction
// is set) and steps its action back. In a wireless game the target is chosen by the frame counter, otherwise by the
// single-player index; the single-player case uses areacheck2.
void em0c_shoot(Entity *e) {
    Entity *target;
    Entity *shot;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        target = playerWork[*(u16 *)frameCounter & 3].entity;
        if (target == NULL) {
            return;
        }
        if ((u32)(target->x.HALF.HI - VARS(Em0cSensor, e)->boxX) > VARS(Em0cSensor, e)->boxWidth ||
            (u32)(target->y.HALF.HI - VARS(Em0cSensor, e)->boxY) > VARS(Em0cSensor, e)->boxHeight) {
            return;
        }
        if (areacheck(e) == 0) {
            return;
        }
        shot = EmGetTama(e, 1, 0);
        if (shot == NULL) {
            return;
        }
        if (!(e->direction & 0x20)) {
            shot->direction = e->direction;
            e->subtimer = e->timer;
        } else {
            shot->direction = GetFacingDirection(e, target);
            e->subtimer = e->timer + (Random() & 3);
        }
        e->action -= 1;
    } else {
        target = playerWork[*Knife_Single_SinglePlay_GetInstance()].entity;
        if (target == NULL) {
            return;
        }
        if ((u32)(target->x.HALF.HI - VARS(Em0cSensor, e)->boxX) > VARS(Em0cSensor, e)->boxWidth ||
            (u32)(target->y.HALF.HI - VARS(Em0cSensor, e)->boxY) > VARS(Em0cSensor, e)->boxHeight) {
            return;
        }
        if (areacheck2(e) == 0) {
            return;
        }
        shot = EmGetTama(e, 1, 0);
        if (shot == NULL) {
            return;
        }
        if (!(e->direction & 0x20)) {
            shot->direction = e->direction;
            e->subtimer = e->timer;
        } else {
            shot->direction = GetFacingDirection(e, target);
            e->subtimer = e->timer + (Random() & 3);
        }
        e->action -= 1;
    }
}
