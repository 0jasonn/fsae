#include "engine/functions.h"
#include "global.h"
#include "enemy/em24.h"
#include "enemy/em24_2.h"
#include "enemy/em24_3.h"

// Functions in this file: em24_damage (0x0203fe7c), em24_init (0x0203fed4), em24_wait (0x0203ff48),
// em24_move (0x0203ff68).

ARM void em24_damage(Entity *e) {
    if (e->child != NULL) {
        if (e->child->iframes == 0) {
            e->child->iframes = 0xf4;
        }
    }
    if (e->action <= 2) {
        e->action = 3;
        charset(e, 0xc);
    }
    GenericKnockback(e, em24_initStateTable);
}

ARM void em24_init(Entity *e) {
    Entity *child = GetTamaWork2(9);
    if (child == NULL) {
        return;
    }
    ObjPosCopy(e, child);
    child->parent = e;
    e->child = child;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->statusFlags |= 0x80;
    e->hitbox = em24_childHitbox;
    e->animationState = Random() & 3;
    em24_waitSet(e);
}

ARM void em24_wait(Entity *e) {
    if (--e->timer == 0) {
        moveSet(e);
    }
}

ARM void em24_move(Entity *e) {
    V(e)->aimTarget = func_02084f98(e, 0x34, 0x34);
    if (V(e)->aimTarget != NULL) {
        aimSet(e);
        return;
    }
    if (--e->timer != 0) {
        if (--e->subtimer == 0) {
            e->subtimer = (Random() & 0x18) + 0x1e;
            e->direction = Random() & 0x18;
            charset(e, 4);
        }
        if (func_020847a0(e) == 0) {
            e->subtimer = 1;
        }
        UpdateAnimationSingleFrame(e);
    } else {
        e->action = 3;
        charset(e, 0xc);
    }
}
