#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/set37_actions.h"

// Set37 heart container actor (module set37). Address -> name:
//   0x0206b648 set37_move (original name)

extern const s8 set37BobTable[]; // set37Table bob offsets, indexed by timer & 7
extern u16 frameCounter;         // frame counter
void adjust(Entity *e);          // 0x0206b768 (set37_2.cpp)

// Bobs up and down every 8 frames. When a player touches it, the player enters state 8 and the actor goes to the
// pick-up demo and adds a heart container to that player.
void set37_move(Entity *e) {
    if ((frameCounter & 7) == 0) {
        e->timer++;
        e->z.HALF.HI = set37BobTable[e->timer & 7] - 8;
    }
    if (!(e->contactFlags & 0x80)) {
        return;
    }
    playerWork[e->contactedEntity->type].state = 8;
    playerWork[e->contactedEntity->type].stateTimer = 1;
    playerWork[e->contactedEntity->type].unk_0b &= 0x7f;
    e->timer = 0x3c;
    e->action++;
    adjust(e);
    e->unk_2e = 0;
    e->statusFlags &= 0x7f;
    AddHeartUtsuwa(e->contactedEntity->type, 1);
}
