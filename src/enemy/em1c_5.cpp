#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em1c.h"

// Functions in this file (actor em1c, original names from the debug build):
//   em1c_wait, em1c_move

extern const u8 data_020d04ec[];   // lengths indexed by timer >> 4
extern const u8 data_020d04f4[];   // timers indexed by Random() & 3
typedef struct Em1cKnifeSlot {
    Entity *first;                  // pointer used when no grabbed object is found (0x94 bytes per slot)
    u8 unk_04[0x90];
} Em1cKnifeSlot;
extern Em1cKnifeSlot data_0212ced8[];

// Wait: counts the shared timer and the own timer down. When the timer ends the actor picks a new timer and direction;
// while it waits it looks for an object to hold (and keeps the shared state updated when the Knife state changes).
ARM void em1c_wait(Entity *e) {
    void *app;

    charMove(e, 0);
    app = KnifeApp_getInstance();
    if (KnifeApp_isWirelessMode(app) == 0) {
        if (em1c_sharedState.unk_00 != *Knife_Single_SinglePlay_GetInstance()) {
            em1c_sharedState.unk_00 = *Knife_Single_SinglePlay_GetInstance();
            em1c_sharedState.timer = 0x5a;
        }
    }
    if (em1c_sharedState.timer != 0) {
        em1c_sharedState.timer -= 1;
    }
    e->timer -= 1;
    if (e->timer == 0) {
        e->action = 2;
        e->timer = data_020d04f4[Random() & 3];
        if (VARS(Vars_Em1c, e)->grabbed != NULL) {
            e->direction = (func_02084fd0(e, VARS(Vars_Em1c, e)->grabbed) + 4) & 0x18;
            return;
        }
        e->direction = Random() & 0x18;
        return;
    }
    if (KnifeApp_isWirelessMode(app) == 0) {
        u8 size = data_020d04ec[e->timer >> 4];
        VARS(Vars_Em1c, e)->grabbed = func_02084f98(e, size, size);
        if (VARS(Vars_Em1c, e)->grabbed == NULL || em1c_sharedState.timer == 0) {
            VARS(Vars_Em1c, e)->grabbed = data_0212ced8[*Knife_Single_SinglePlay_GetInstance()].first;
        }
        if (VARS(Vars_Em1c, e)->grabbed != NULL) {
            e->direction = (GetFacingDirection(e, VARS(Vars_Em1c, e)->grabbed) + 4) & 0x18;
        }
    }
    if (VARS(Vars_Em1c, e)->grabbed != NULL) {
        return;
    }
    {
        u8 size = data_020d04ec[e->timer >> 4];
        Entity *found = func_02084f98(e, size, size);
        VARS(Vars_Em1c, e)->grabbed = found;
        if (found == NULL) {
            return;
        }
        e->direction = (GetFacingDirection(e, found) + 4) & 0x18;
    }
}

// Move: the actor walks with charMove, and stops at the end of its timer or when a grab is possible (the input bit 0x80).
ARM void em1c_move(Entity *e) {
    void *app;
    u32 input;

    app = KnifeApp_getInstance();
    if (KnifeApp_isWirelessMode(app) == 0) {
        if (em1c_sharedState.unk_00 != *Knife_Single_SinglePlay_GetInstance()) {
            em1c_sharedState.unk_00 = *Knife_Single_SinglePlay_GetInstance();
            em1c_sharedState.timer = 0x5a;
        }
    }
    if (em1c_sharedState.timer != 0) {
        em1c_sharedState.timer -= 1;
    }
    charMove(e, 0x10);
    if (VARS(Vars_Em1c, e)->cooldown != 0) {
        VARS(Vars_Em1c, e)->cooldown -= 1;
    }
    if (func_020847a0(e) == 0) {
        e->timer = 1;
    }
    e->timer -= 1;
    if (VARS(Vars_Em1c, e)->cooldown == 0) {
        input = func_02084ac8(e, 0x10);
        if ((input & 0x80) != 0) {
            if (KnifeApp_isWirelessMode(app) == 0) {
                if (em1c_sharedState.timer != 0) {
                    return;
                }
                e->action = 3;
                e->timer = 0x10;
                e->subtimer = 1;
                e->direction = (GetFacingDirection(e, VARS(Vars_Em1c, e)->grabbed) + 4) & 0x18;
                return;
            }
            e->action = 3;
            e->timer = 0x10;
            e->subtimer = 1;
            e->direction = input & 0x18;
            return;
        }
    }
    if (e->timer == 0) {
        em1c_waitSet(e);
    }
}
