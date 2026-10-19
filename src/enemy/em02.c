#include "engine/entity.h"
#include "global.h"

typedef struct Vars_02030790 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 unk_7c;
} Vars_02030790;

extern const EntityFunc data_020d08e4[];
extern const EntityFunc data_020d08fc[];
extern const u8 data_020d08cc[];

ARM void func_02030790(Entity *e) {
    EnemyFunctionHandler(e, data_020d08e4);
}

ARM void em02_normal(Entity *e) {
    data_020d08fc[e->action](e);
}

ARM void em02_damage(Entity *e) {
    if (e->health != 0 && VARS(Vars_02030790, e)->unk_7c != e->health) {
        e->action = 6;
        return;
    }
    GenericKnockback(e, data_020d08e4);
}

ARM void em02_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d08cc;
    InitAnimationForceUpdate(e, 0);
    e->action++;
    e->timer = (Random() + 0x1e) & 0x3c;
    VARS(Vars_02030790, e)->unk_7c = e->health;
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
