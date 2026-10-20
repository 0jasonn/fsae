#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"
#include "object/set13.h"

// Set13 actor, third unit (module set13). Address -> name:
//   0x02064690 set13_move1 (original name)

ARM void set13_move1(Entity *e) {
    if (cellcheck(e)) {
        return;
    }
    switch (e->type2) {
    case 0:
    case 1:
        break;
    case 2:
        if (VARS(Vars_Set13, e)->typeBits != (VARS(Vars_Set13, e)->typeBits & em12_typeMasks[e->areaIndex])) {
            e->action = 1;
            return;
        }
        break;
    case 3:
        if (VARS(Vars_Set13, e)->typeMask76 == (VARS(Vars_Set13, e)->typeBits & em12_typeMasks[e->areaIndex])) {
            e->subtimer = 0xff;
        } else {
            e->subtimer = 1;
        }
        break;
    default:
        break;
    }
    e->subtimer = e->subtimer - 1;
    if (e->subtimer != 0) {
        return;
    }
    e->action = 2;
    e->subtimer = 8;
    hidari_rewritecell(e);
    e->animationState = (e->animationState + VARS(Vars_Set13, e)->step) & 0x3;
    InitAnimationForceUpdate(e, e->animationState);
    EnqueueSFX(0x57);
}
