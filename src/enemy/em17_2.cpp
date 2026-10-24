#include "engine/functions.h"
#include "global.h"
#include "enemy/em17.h"
// Actor em17 (module em17), unit 2. Address -> name:
//   0x0203d5f0 em17_buttobi, 0x0203d628 em17_init, 0x0203d67c em17_move, 0x0203d7a8 em17_lift,
//   0x0203d7dc em17_lift_init, 0x0203d818 em17_nop (empty handler), 0x0203d81c em17_lift_throw,
//   0x0203d8a8 em17_lift_end

// File-local overlay. The shared Vars_em17 (enemy/em17.h) has a stray unk_71 byte after the 2-byte field70 union,
// which moves carryFlag and carryTimer one byte up. The ROM uses 0x72 and 0x73, so this unit declares them itself.
typedef struct Vars_em17_2 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target; // entity being carried / lifted (set in em17_move)
    /* 68 */ u8 unk_68[0x8];
    /* 70 */ union {
        u8 liftFlag;    // set by em17_batabata, cleared by em17_lift_throw
        u16 shakeTimer; // countdown in buruburu, also set by em17_fall
    } field70;
    /* 72 */ u8 carryFlag;  // non-zero while the actor carries its target
    /* 73 */ u8 carryTimer; // frames until the carry is dropped
} Vars_em17_2;

#define V2(e) VARS(Vars_em17_2, e)

// Runs func_02084788, then while the actor is in pose 0x26 (lifted) its base direction goes through the wall check
// func_02085a60 as the direction and is stored back into the base direction.
ARM void em17_buttobi(Entity *e) {
    func_02084788(e);
    if (e->poseId != 0x26) {
        return;
    }
    e->direction = e->baseDirection;
    func_02085a60(e, e->wallFlags);
    e->baseDirection = e->direction;
}

// Init: sprite priority, the status flags, the hitbox, timer 1, action 1 and animation 0.
ARM void em17_init(Entity *e) {
    e->action = 1;
    e->timer = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->hitbox = em17_hitbox;
    e->unk_1a = 0;
    e->statusFlags |= 0x10;
    e->animationState = 0;
    InitAnimationForceUpdate(e, 0);
}

// Move: when func_02084f98 returns an entity (not NULL), it becomes the new target and the old target becomes the
// child; carryFlag is set and carryTimer is 4. While carrying, the direction faces the target (averaged with the child
// when there is one) and the carry is dropped when carryTimer runs out. Without a carry it picks a random direction
// every 0x1e frames.
ARM void em17_move(Entity *e) {
    Entity *child;

    if (UpdateGravity(e, 0x1800)) {
        return;
    }
    child = func_02084f98(e, 0x38, 0x38);
    if (child != NULL) {
        if (V2(e)->target != NULL) {
            e->child = V2(e)->target;
        }
        V2(e)->carryFlag = 1;
        V2(e)->carryTimer = 4;
        if (child == V2(e)->target) {
            e->child = NULL;
        }
        V2(e)->target = child;
    } else if (V2(e)->carryTimer != 0) {
        V2(e)->carryTimer--;
        if (V2(e)->carryTimer == 0) {
            V2(e)->target = NULL;
            e->child = NULL;
            V2(e)->carryFlag = 0;
            e->timer = 1;
        }
    }
    if (V2(e)->carryFlag != 0) {
        e->direction = (GetFacingDirection(V2(e)->target, e) + 4) & 0x1f;
        if (e->child != NULL) {
            e->direction = ((e->direction + GetFacingDirection(e->child, e) - 4) / 2) & 0x1f;
        }
    } else {
        e->timer--;
        if (e->timer == 0) {
            e->timer = 0x1e;
            e->direction = (Random() & 0x18) + 4;
        }
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}

// Lift: runs the lift handler of the current sub action, then buruburu while the sub action is below 2.
ARM void em17_lift(Entity *e) {
    em17_liftTable[e->subAction](e);
    if (e->subAction < 2) {
        buruburu(e);
    }
}

// Lift init: sub action 1, timer 4, clears the top status bit, animation 6.
ARM void em17_lift_init(Entity *e) {
    e->subAction = 1;
    e->timer = 4;
    e->statusFlags &= 0x7f;
    e->animationState = 6;
    InitAnimationForceUpdate(e, 6);
    e->unk_2e = 0;
}

// Empty handler (the table entry for an action that does nothing).
ARM void em17_nop(Entity *e) {
}

// Throw of the lifted object: after the timer, it flies with speed 0x180 and its throw hitbox.
ARM void em17_lift_throw(Entity *e) {
    e->unk_2e = 5;
    if (e->direction == 0xff) {
        return;
    }
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->unk_1a = 0;
    e->action = 3;
    e->speed = 0x180;
    e->zVelocity = 0;
    e->statusFlags |= 0x80;
    e->poseId = 7;
    e->attackKnockback = 0xc;
    e->iframes = 0xf8;
    e->hitbox = em17_throwHitbox;
    V2(e)->field70.liftFlag = 0;
    e->animationState = 8;
    InitAnimationForceUpdate(e, 8);
}

// End of a lift: action 6, animation 5 and the lift hitbox.
ARM void em17_lift_end(Entity *e) {
    e->action = 6;
    e->unk_1a = 0;
    e->statusFlags |= 0x80;
    e->hitbox = em17_hitboxLift;
    e->animationState = 5;
    InitAnimationForceUpdate(e, 5);
    e->unk_2e = 5;
}
