#include "engine/functions.h"
#include "global.h"
// SeqSet: sets the animation state and restarts the animation. Facing above 0x10 uses the sequence itself,
// otherwise the one after it (animation pairs).
void em08_seqSet(Entity *e, u8 seq) {
    if (e->direction > 0x10) {
        if (e->animationState == seq) return;
        e->animationState = seq;
        InitAnimationForceUpdate(e, e->animationState);
    } else {
        int next = seq + 1;
        if (e->animationState == next) return;
        e->animationState = next;
        InitAnimationForceUpdate(e, e->animationState);
    }
}
