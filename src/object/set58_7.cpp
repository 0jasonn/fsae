#include "engine/functions.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/set58.h"

// Set58 helpers, third unit (module set58). Address -> name:
//   0x020742cc set58_actionInit (provisional name; sets action 1 and forces the animation)
//   0x020742e4 setYouseiEffect (original name)

ARM void set58_actionInit(Entity *e) {
    e->action = 1;
    InitAnimationForceUpdate(e, 0);
}

ARM void setYouseiEffect(Entity *e) {
    Entity *child;

    if (e->timer != 0) {
        e->timer--;
        return;
    }
    child = GetSetWork(0x58, 8, 0);
    if (child == NULL) {
        return;
    }
    ObjPosCopy(e, child);
    e->timer = 0x30;
}
