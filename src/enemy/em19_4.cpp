#include "engine/functions.h"
#include "global.h"
#include "enemy/em19.h"
#include "enemy/em19_4.h"

// Functions in this file: em19_damage (0x0203e0c8), em19_init (0x0203e1c4).

ARM void em19_damage(Entity *e) {
    if (e->unk_42 != 0 && e->action != 3 && e->action < 7) {
        e->action = 3;
        e->timer = 0;
        e->spriteSettings.b0 = 1;
        e->animationState = 2;
        InitAnimationForceUpdate(e, 2);
    }
    if (VARS(Vars_em19, e)->lastHealth != e->health || e->unk_43 != 0) {
        if (e->parent != NULL) {
            effectset(e->parent);
            e->parent->health = 0;
            e->parent = NULL;
            if (e->unk_43 != 0) {
                e->spriteSettings.b0 = 1;
                e->animationState = 2;
                InitAnimationForceUpdate(e, 2);
            }
        }
        if (e->action < 7) {
            e->action = 7;
        }
        VARS(Vars_em19, e)->lastHealth = e->health;
    }
    if (e->zVelocity == 0x18000 && e->contactFlags == 0x80) {
        e->zVelocity = 0;
    }
    GenericKnockback(e, em19_stateTable);
}

ARM void em19_init(Entity *e) {
    u8 type;
    u8 health;
    u16 pose;
    e->action = 1;
    e->unk_2e = 2;
    e->hitbox = em19_hitbox;
    type = e->parent->type;
    health = e->health;
    pose = em19_poseTable[type];
    VARS(Vars_em19, e)->lastHealth = health;
    e->poseId = pose;
    VARS(Vars_em19, e)->moveTimer = (Random() & 0x1f) + 0x1e;
}
