#include "Unknown/B/Actor_0204112c.h"
#include "global.h"

// Enemy_CheckAttackFrame (0x02041344): switches to action 7 when the attack frame ends; sets unk_3f otherwise.
ARM void Enemy_CheckAttackFrame(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = 7;
        InitAnimationForceUpdate(e, e->animationState);
        return;
    }
    if (e->frame != 0) {
        e->unk_3f = 0x3c;
    } else {
        e->unk_3f = 0x3b;
    }
}

// Enemy_IdleThenMove (0x0204138c): when the idle timer runs out, moves at speed 0x100 in action 1.
ARM void Enemy_IdleThenMove(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action = 1;
    e->speed = 0x100;
    V(e)->idleTimer = 0x3c;
}

// Enemy_AllocChildIfUnclaimed (0x020413bc): allocates a 0x68-byte child and returns it only when no
// other player claims it. Returns NULL otherwise.
ARM Entity *Enemy_AllocChildIfUnclaimed(Entity *e) {
    Entity *child = func_02084f98(e, 0x68, 0x40);
    if (child == NULL) {
        return NULL;
    }
    if (func_0208de54(func_0208da4c()) == 0) {
        if (child != data_0212ceb0[*func_02093b5c()].entity) {
            return NULL;
        }
        if (data_021348cc.unk_0 != 0) {
            return NULL;
        }
    }
    if (data_0212ceb0[child->type].unk_36 & 0x1091) {
        return NULL;
    }
    return child;
}

// Enemy_StartFacingAction (0x02041458): enters action 4 facing the target.
ARM void Enemy_StartFacingAction(Entity *e, Entity *target) {
    e->action = 4;
    e->timer = 8;
    V(e)->target = target;
    e->direction = GetFacingDirection(e, target);
    e->animationState = e->direction >> 3;
    InitAnimationForceUpdate(e, e->animationState);
}
