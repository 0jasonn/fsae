#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "enemy/em1c.h"

// Actor em1c, attack entry (unit 2 of em1c; em1c_attack and charMove are parked in scratch/agentE/nonmatching).
ARM void em1c_attackInit(Entity *e) {
    charMove(e, 0);
    if ((e->subtimer & 0x2) == 0) {
        return;
    }
    e->action = 4;
    InitAnimationForceUpdate(e, (u8)(e->animationState + 0x20));
}
