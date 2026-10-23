#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "enemy/em1c.h"

// Actor em1c, attack end (unit 3). Calls charMove, defined in scratch/agentE/nonmatching/charMove.cpp.
ARM void em1c_attackEnd(Entity *e) {
    charMove(e, 0);
    if (e->subtimer == 0) {
        em1c_waitSet(e);
        VARS(Vars_Em1c, e)->cooldown = 0x78;
    }
}
