#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em12_wait2.h"

// Functions in this file: em12_wait2 (0x0203b594).

// When the target area holds the chosen player the actor turns to it and starts the approach animation.
// In wireless mode the player comes from the frame counter, otherwise the local player's index is used.
void em12_wait2(Entity *e) {
    Entity *target;

    target = *(Entity **)&data_0212ced8[(frameCounter.frame & 3) * 0x94];
    if (!tgtareacheck(e, target)) {
        return;
    }
    e->action = 3;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        e->child = *(Entity **)&data_0212ced8[(frameCounter.frame & 3) * 0x94];
    } else {
        e->child = *(Entity **)&data_0212ced8[*Knife_Single_SinglePlay_GetInstance() * 0x94];
    }
    target = e->child;
    e->direction = (GetFacingDirection(e, target) + 4) & 0x18;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, 0xa);
}
