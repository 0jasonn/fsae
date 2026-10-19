#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

typedef struct Vars_02030790 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 lastHealth; // health seen at the last hit check
} Vars_02030790;

extern const EntityFunc em02_actions[];
extern const EntityFunc em02_normalActions[];
extern const u8 em02_hitbox[];

ARM void em02_main(Entity *e) {
    EnemyFunctionHandler(e, em02_actions);
}

ARM void em02_normal(Entity *e) {
    em02_normalActions[e->action](e);
}

ARM void em02_damage(Entity *e) {
    if (e->health != 0 && VARS(Vars_02030790, e)->lastHealth != e->health) {
        e->action = 6;
        return;
    }
    GenericKnockback(e, em02_actions);
}

ARM void em02_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = em02_hitbox;
    InitAnimationForceUpdate(e, 0);
    e->action++;
    e->timer = (Random() + 0x1e) & 0x3c;
    VARS(Vars_02030790, e)->lastHealth = e->health;
}

ARM void em02_wait(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action++;
    e->timer = 0x48;
    e->direction = Random() & 0x18;
    InitAnimationForceUpdate(e, (e->direction >> 3) + 1);
}

ARM void em02_move(Entity *e) {
    if (--e->timer != 0) {
        if (e->frame == 0) {
            func_020852ec(e);
        }
        UpdateAnimationSingleFrame(e);
        return;
    }
    if (Random() & 7) {
        e->action--;
        e->timer = (Random() + 0x1e) & 0x3c;
        InitAnimationForceUpdate(e, 0);
        return;
    }
    e->action++;
    InitAnimationForceUpdate(e, 5);
}

ARM void em02_vanish(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        return;
    }
    if (e->frame == 1) {
        e->unk_3c &= 0x7f;
        return;
    }
    e->action++;
    e->timer = 0x78;
    e->spriteSettings.b0 = 0;
}

ARM void em02_vwait(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    e->action++;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, 6);
}

ARM void em02_appear(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        return;
    }
    if (e->frame == 1) {
        e->unk_3c |= 0x80;
        return;
    }
    e->action = 1;
    e->timer = (Random() + 0x1e) & 0x3c;
    InitAnimationForceUpdate(e, 0);
}
