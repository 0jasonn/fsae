#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"
#include "object/set13.h"

// Set13 actor, second unit (module set13). Address -> name:
//   0x020645a4 set13_wait (original name)

ARM void set13_wait(Entity *e) {
    u32 bits;

    bits = VARS(Vars_Set13, e)->typeBits;
    if (bits != (bits & em12_typeMasks[e->areaIndex])) {
        return;
    }
    if (e->type2 == 1) {
        VARS(Vars_Set13, e)->typeBits = 0;
    }
    e->action = 2;
    e->subtimer = 8;
    hidari_rewritecell(e);
    e->animationState = (e->animationState + VARS(Vars_Set13, e)->step) & 0x3;
    InitAnimationForceUpdate(e, e->animationState);
    EnqueueSFX(0x57);
}
