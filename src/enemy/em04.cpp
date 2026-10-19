#include "engine/functions.h"
#include "enemy/em03.h"
#include "global.h"

ARM void em03_release(Entity *e) {
    func_020847a0(e);
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    e->action = 5;
    e->speed -= 0x40;
    e->unk_5e.b0 = 2;
    InitAnimationForceUpdate(e, 4);
}

ARM void aibou_check(Entity *e) {
    if (e->linkedEntity == 0) {
        return;
    }
    Entity *parentEntity = e->parent;
    if (parentEntity == 0) {
        return;
    }
    if (e->type2 == 1) {
        e->unk_64[4] = 0;
        parentEntity->type2 = 0;
    }
}

ARM void em04_main(Entity *e) {
    EnemyFunctionHandler(e, em04_actions);
}

ARM void em04_normal(Entity *e) {
    em04_normalActions[e->action](e);
}

ARM void em04_damage(Entity *e) {
    if (e->action == 3) {
        e->action = 1;
        e->speed = 0x80;
        e->subtimer = 0x14;
    }
    GenericKnockback(e, em04_actions);
}

ARM void em04_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = em04_hitbox;
    InitAnimationForceUpdate(e, 0);
    e->animationState = 0;
    e->action++;
}
