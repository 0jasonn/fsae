#include "engine/functions.h"
#include "global.h"
#include "object/effect_tuto0.h"

// effect_tuto0 family (module effect_tuto0), 0x0206dadc .. 0x0206db30 (effect_tuto0_init, 0x0206da74, is parked in scratch/agentA/nonmatching).
// Address -> name: 0x0206dadc effect_tuto0_move

ARM void effect_tuto0_move(Entity *e) {
    if (e->subtimer == 0) {
        e->spriteSettings.b0 = 1;
    } else {
        e->subtimer--;
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (e->type2 == KNIFE_CURSOR_INDEX()) {
        return;
    }
    PutObjWork(e);
}
