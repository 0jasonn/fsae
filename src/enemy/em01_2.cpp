#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

void dirSeqSet(Entity *e);

ARM void em01_stop(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0x80) {
        e->timer = 0x3c;
        e->action = 1;
    }
}


ARM void dirSeqSet(Entity *e) {
    u8 animState = EmCharDir2(e->direction);

    if (animState == 0xff || animState == e->animationState) {
        return;
    }
    e->animationState = animState;
    InitAnimationForceUpdate(e, animState);
}
