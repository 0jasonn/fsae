#include "engine/functions.h"
#include "enemy/em15.h"
#include "global.h"
// Renames (renames.txt): em15_damage -> em15_damage, em15_targetInit -> em15_targetInit

ARM void Em15(Entity *e) {
    if (V(e)->entryFlag == 1) {
        e->unk_6b = 0;
    }
    EnemyFunctionHandler(e, em15_stateTable);
}

ARM void em15_normal(Entity *e) {
    em15_actionTable[e->action](e);
}

ARM void em15_damage(Entity *e) {
    GenericKnockback(e, em15_stateTable);
}

ARM void em15_stop(Entity *e) {
    func_02084f54(e);
    if (e->unk_43 == 0) {
        e->z.HALF.HI = -2;
    }
}

ARM void em15_init(Entity *e) {
    e->action = 1;
    e->z.HALF.HI = -2;
    V(e)->waitFrames = (u16)((e->timer + 1) * 30);
    e->unk_2e = 5;
    e->hitbox = em15_hitbox;
}

ARM void em15_targetInit(Entity *e) {
    e->action = 2;
    WizGetTarget(e);
}

ARM void em15_getpos_03cd90(Entity *e) {
    if (!em15_getpos_03cf18(e)) {
        return;
    }
    e->action = 3;
    e->timer = 0x10;
    func_02085f98(e, 0x5c);
}

ARM void em15_appear(Entity *e) {
    UpdateAnimationSingleFrame(e);
    WizWarpAppear(e);
    if (e->timer != 0) {
        return;
    }
    e->action = 4;
    e->timer = 0x10;
    e->statusFlags |= 0x80;
}

ARM void em15_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    Entity *tama = GetTamaWork(5);
    if (tama == NULL) {
        e->timer++;
        return;
    }
    tama->type = 3;
    tama->direction = (e->direction - 3) & 0x1f;
    tama->parent = e;
    e->action = 5;
    e->timer = 0x69;
    InitAnimationForceUpdate(e, (e->animationState + 4) & 0xff);
}

ARM void em15_attack(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action = 6;
    WizVanishInit(e);
}

ARM void em15_vanish(Entity *e) {
    UpdateAnimationSingleFrame(e);
    WizWarpVanish(e);
    if (e->timer != 0) {
        return;
    }
    e->action = 7;
    V(e)->waitTimer = V(e)->waitFrames;
    e->spriteSettings.b0 = 0;
}

ARM void em15_wait(Entity *e) {
    V(e)->waitTimer--;
    if (V(e)->waitTimer == 0) {
        e->action = 1;
    }
}
