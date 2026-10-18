#include "Unknown/B/Actor_0204112c.h"
#include "global.h"

// Enemy_EndPartsAction13 (0x0204294c): advances the parts; when the frame flag is set, goes to action 0xd, clears
// the parent's flag byte and deletes both parts.
ARM void Enemy_EndPartsAction13(Entity *e) {
    UpdateAnimationSingleFrame(VP(e)->partA);
    UpdateAnimationSingleFrame(VP(e)->partB);
    UpdateAnimationSingleFrame(e);
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 0xd;
    e->parent->unk_6c[4] = 0;
    InitAnimationForceUpdate(e, 0);
    DeleteEntity(VP(e)->partA);
    DeleteEntity(VP(e)->partB);
}

// Enemy_WaitForParentFlags (0x020429a8): while the parent's low flags are set, waits in action 1 for 0x3c frames.
ARM void Enemy_WaitForParentFlags(Entity *e) {
    if (e->parent->unk_6c[4] & 3) {
        e->action = 1;
        e->timer = 0x3c;
    }
}
