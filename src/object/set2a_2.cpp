#include "engine/functions.h"
#include "global.h"

// Set2a actor, second unit (module set2a). Address -> name:
//   0x0205a560 set2a_move (original name)

ARM void set2a_move(Entity *e) {
    u8 timer;
    UpdateAnimationSingleFrame(e);
    if (e->type != 1) {
        return;
    }
    timer = e->timer;
    e->timer = timer - 1;
    if (timer != 0) {
        return;
    }
    PutObjWork(e);
}
