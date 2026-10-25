#include "engine/functions.h"
#include "global.h"
#include "enemy/em22.h"

// Functions in this file: em22_normal (0x0203f754).

ARM void em22_normal(Entity *e) {
    dmgmgr(e);
    em22_actionTable[e->action](e);
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    if (e->animationState != 4) {
        return;
    }
    e->animationState = 0;
    InitAnimationForceUpdate(e, 0);
}
