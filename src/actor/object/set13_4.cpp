#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/g_callees.h"
#include "actor/object/set13.h"

// Set13 actor (module set13). Address -> name:
//   0x0206461c set13_move0 (original name)

void set13_move0(Entity *e) {
    u8 nextAction;
    u8 timer;
    e->subtimer = e->subtimer - 1;
    if (e->subtimer != 0) {
        return;
    }
    nextAction = 3;
    e->action = nextAction;
    timer = e->timer;
    e->subtimer = timer;
    VARS(Vars_Set13, e)->typeMask76 = VARS(Vars_Set13, e)->typeBits & em12_typeMasks[e->areaIndex];
    e->animationState = (e->animationState + VARS(Vars_Set13, e)->step) & 0x3;
    InitAnimationForceUpdate(e, e->animationState);
    hidari_writecell(e);
    EnqueueSFX(0x57);
}
