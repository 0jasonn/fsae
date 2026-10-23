#include "engine/functions.h"
#include "global.h"
#include "enemy/em16.h"
// Actor em16 (module em16), unit 3. Address -> name:
//   0x0203d29c em16_kiran, 0x0203d31c em16_nage, 0x0203d3ac em16_watch, 0x0203d3fc em16_dush,
//   0x0203d440 kyoroSet, 0x0203d474 frontCheck

// Action 6: when the timer runs out, it attacks the target with speed 0x200 and knockback 0x14 (action 8),
// or drops its child and goes to action 6 when there is no target.
ARM void em16_kiran(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    if (V(e)->target != NULL) {
        e->action = 8;
        e->speed = 0x200;
        e->attackKnockback = 0x14;
        InitAnimationForceUpdate(e, e->animationState + 8);
    } else {
        e->action = 6;
        e->child = NULL;
        InitAnimationForceUpdate(e, e->animationState + 0xc);
    }
}

// Action 7 (throw): with frame bit 0x80 set, returns to kyoroSet or starts the child's action 7. Otherwise, when the
// frame counter is set, it fires a new projectile (EmGetTama kind 7) and gives it the actor's direction.
ARM void em16_nage(Entity *e) {
    Entity *tama;

    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        if (e->child != NULL) {
            e->action = 7;
            InitAnimationForceUpdate(e, e->animationState);
        } else {
            kyoroSet(e);
        }
        return;
    }
    if (e->frame == 0) {
        return;
    }
    tama = EmGetTama(e, 7, 0);
    if (tama == NULL) {
        return;
    }
    tama->direction = e->direction;
    tama->parent = e;
    e->frame = 0;
    e->child = tama;
    V(e)->target = NULL;
    V(e)->waitTimer = 0x3c;
}

// Action 8 (watch): with a child, and a target, the actor starts the attack (speed 0x200, knockback 0x14).
ARM void em16_watch(Entity *e) {
    if (e->child != NULL) {
        if (V(e)->target == NULL) {
            return;
        }
        e->action = 8;
        e->speed = 0x200;
        e->attackKnockback = 0x14;
        InitAnimationForceUpdate(e, e->animationState + 8);
    } else {
        kyoroSet(e);
    }
}

// Dash: once the actor is not blocked (func_020847a0 is zero), it turns around and moves with speed 0x80.
ARM void em16_dush(Entity *e) {
    func_02085990(e);
    if (func_020847a0(e) != 0) {
        return;
    }
    e->speed = 0x80;
    e->attackKnockback = 0xc;
    e->direction = e->direction ^ 0x10;
    kyoroSet(e);
}

// Starts the walk: action 1, no target, the animation for the current direction (index + 4).
ARM void kyoroSet(Entity *e) {
    e->action = 1;
    V(e)->target = NULL;
    e->animationState = e->direction >> 3;
    InitAnimationForceUpdate(e, (u8)(e->animationState + 4));
}

// Returns 1 while the wait timer runs or the direction does not match func_02084ac8(e, 0xc). Otherwise it spawns a
// 0x38-byte child (the target, when there is one), starts action 5 and returns 0.
ARM BOOL frontCheck(Entity *e) {
    Entity *child;

    if (V(e)->waitTimer == 0) {
        if ((u32)(e->direction | 0x80) == func_02084ac8(e, 0xc)) {
            child = func_02084f98(e, 0x38, 0x38);
            if (child != NULL) {
                V(e)->target = child;
                e->timer = 0x1e;
            } else {
                V(e)->target = NULL;
                e->timer = 0x10;
            }
            e->action = 5;
            InitAnimationForceUpdate(e, em16_animTable[e->animationState]);
            return 0;
        }
    } else {
        V(e)->waitTimer--;
    }
    return 1;
}
