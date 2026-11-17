#include "engine/functions.h"
#include "global.h"
#include "actor/object/set66.h"

// Set69 actor, wait states (module set69). Address -> name (original names):
//   0x02075c14 type0_wait1, 0x02075e78 type0_wait4

// type0_wait1 (0x02075c14): when the timer runs out, puts every player into the state 0xf with motion 0x1b1.
void type0_wait1(Entity *e) {
    u8 i;
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 6;
    e->timer = 0x10;
    for (i = 0; i < gameState.playerCount; i++) {
        playerWork[i].state = 0xf;
        playerWork[i].motionId = 0x1b1;
        playerWork[i].stateTimer = e->timer + 0x96;
        playerWork[i].unk_39 = 1;
    }
}
