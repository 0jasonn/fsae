#include "enemy/em28.h"
#include "global.h"

// type0_attackClose (0x0204294c): advances the parts; when the frame flag is set, goes to action 0xd, clears
// the parent's flag byte and deletes both parts.
ARM void type0_attackClose(Entity *e) {
    UpdateAnimationSingleFrame(VP(e)->partA);
    UpdateAnimationSingleFrame(VP(e)->partB);
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0xd;
    e->parent->unk_6c[4] = 0;
    InitAnimationForceUpdate(e, 0);
    PutObjWork(VP(e)->partA);
    PutObjWork(VP(e)->partB);
}

// type0_attackEnd (0x020429a8): while the parent's low flags are set, waits in action 1 for 0x3c frames.
ARM void type0_attackEnd(Entity *e) {
    if (e->parent->unk_6c[4] & 3) {
        e->action = 1;
        e->timer = 0x3c;
    }
}
