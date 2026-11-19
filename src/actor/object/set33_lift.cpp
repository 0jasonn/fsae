#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/set33_actions.h"

// Set33 actor (module set33). Address -> name:
//   0x0206a830 set33_lift (original name)

// Throws the lifted platform: flags the riders selected by the timer bits and launches the actor upwards.
void set33_lift(Entity *e) {
    if (e->type2 == 0) {
        return;
    }
    if (e->timer & 1) {
        playerWork[0].unk_39 = 1;
    }
    if (e->timer & 2) {
        playerWork[1].unk_39 = 1;
    }
    if (e->timer & 4) {
        playerWork[2].unk_39 = 1;
    }
    if (e->timer & 8) {
        playerWork[3].unk_39 = 1;
    }
    e->action = 3;
    e->speed = set33SpeedTable[e->type];
    e->direction ^= 0x10;
    e->zVelocity = 0xc000;
    e->unk_2e = set33Unk2eTable[e->type];
    EnqueueSFX(0xc);
}
