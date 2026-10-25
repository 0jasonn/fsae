#include "engine/functions.h"
#include "global.h"
#include "enemy/em21.h"
#include "enemy/em21_2.h"

// Functions in this file: em21_die (0x0203f27c), em21_init (0x0203f2d8), em21_revivalwait (0x0203f3c4),
// em21_move (0x0203f428), em21_jumpInit (0x0203f4d8), em21_jump (0x0203f548), em21_jumpEnd (0x0203f5b4).

ARM void em21_die(Entity *e) {
    Entity *child = GetEnemyWork(0x21);
    if (child != NULL) {
        ObjPosCopy(e, child);
        child->x.HALF.HI = VARS(Vars_em21, e)->posX;
        child->y.HALF.HI = VARS(Vars_em21, e)->posY;
        child->z.HALF.HI = 0;
        VARS(Vars_em21, child)->revivalTimer = 0x23a;
        child->type = e->type;
    }
    EmDie(e);
}

ARM void em21_init(Entity *e) {
    int dir;
    e->unk_2e = 5;
    e->hitbox = em21_hitbox;
    e->timer = 0xf0;
    dir = Random() & 0x1c;
    e->direction = dir;
    e->animationState = dir >> 2;
    VARS(Vars_em21, e)->posX = e->x.HALF.HI;
    VARS(Vars_em21, e)->posY = e->y.HALF.HI;
    VARS(Vars_em21, e)->waitTimer = (Random() & 0x70) + 0xf0;
    if (VARS(Vars_em21, e)->revivalTimer != 0) {
        e->action = 1;
        e->statusFlags &= 0x7f;
        InitAnimationForceUpdate(e, 0xc);
    } else {
        e->action = 2;
        e->spriteSettings.b0 = 1;
        InitAnimationForceUpdate(e, e->animationState);
    }
    if (e->type == 1) {
        e->spriteSettings.b20 = 0xd;
        e->spriteSettings.b16 = e->spriteSettings.b20;
        VARS(Vars_em21, e)->waitTimer = (Random() & 0x40) + 0x78;
    }
}

ARM void em21_revivalwait(Entity *e) {
    if (e->type == 1) {
        return;
    }
    if (--VARS(Vars_em21, e)->revivalTimer == 0) {
        e->action = 2;
        e->statusFlags |= 0x80;
        InitAnimationForceUpdate(e, e->animationState);
        return;
    }
    if (VARS(Vars_em21, e)->revivalTimer == 0x5a) {
        e->spriteSettings.b0 = 1;
    }
    UpdateAnimationSingleFrame(e);
}

ARM void em21_move(Entity *e) {
    int dir;
    u8 result;
    result = em21_crossCheck(e);
    if ((result & 0x80) != 0) {
        e->action = 3;
        e->timer = 0x10;
        e->direction = result & 0x18;
        e->statusFlags &= 0x7f;
        InitAnimationForceUpdate(e, 0xc);
        return;
    }
    UpdateAnimationSingleFrame(e);
    func_02084828(e);
    if (--e->timer != 0) {
        if (e->wallFlags == 0) {
            return;
        }
    }
    e->timer = 0xf0;
    e->statusFlags |= 0x80;
    dir = Random() & 0x1c;
    e->direction = dir;
    e->animationState = dir >> 2;
    InitAnimationForceUpdate(e, e->animationState);
}

ARM void em21_jumpInit(Entity *e) {
    u8 anim;
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 4;
    e->speed = 0x180;
    e->zVelocity = 0x1c000;
    e->statusFlags |= 0x80;
    e->poseId = 0x33;
    anim = (e->direction >> 3) + 8;
    InitAnimationForceUpdate(e, anim);
    MizupochaSet(e);
}

ARM void em21_jump(Entity *e) {
    UpdateAnimationSingleFrame(e);
    func_02084828(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    e->action = 5;
    e->timer = 0x10;
    e->speed = 0x80;
    e->statusFlags &= 0x7f;
    e->poseId = 0x32;
    InitAnimationForceUpdate(e, 0xc);
    MizupochaSet(e);
}

ARM void em21_jumpEnd(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 2;
    e->timer = 1;
    VARS(Vars_em21, e)->waitTimer = (Random() & 0x70) + 0xf0;
    if (e->type != 1) {
        return;
    }
    VARS(Vars_em21, e)->waitTimer = (Random() & 0x40) + 0x78;
}
