#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em23.h"
#include "actor/enemy/em23_6.h"
#include "engine/player.h"
#include "actor/enemy/em23_4.h"
#include "actor/enemy/em23_3.h"
#include "actor/enemy/em23_5.h"

// Functions in this file: Em23 (0x0203fa4c).

void Em23(Entity *e) {
    if (e->type2 == 0) {
        func_02084700(e);
        em23_stateTable[func_02084a30(e)](e);
        fuwafuwa(e);
        UpdateAnimationSingleFrame(e);
        func_0208ae30(e);
        e->spriteSettings.b30 = 1;
        e->spriteSettings.b14 = 1;
    } else {
        enrinMove(e);
    }
}

// Functions in this file: em23_normal (0x0203fac0).

void em23_normal(Entity *e) {
    em23_actionTable[e->action](e);
}

// Functions in this file: em23_damage (0x0203fadc).

void em23_damage(Entity *e) {
    if (e->type != 0) {
        e->action = 1;
    } else {
        e->action = 3;
        e->timer = 0x1e;
        e->statusFlags &= 0x7f;
    }
    if ((data_0212ceb0[e->contactedEntity->type].statusFlags & 0x4000) == 0) {
        Entity *child = GetEnemyWork(0x23);
        if (child != NULL) {
            Entity *contacted;
            child->type = e->type;
            child->type2 = 1;
            contacted = e->contactedEntity;
            child->child = contacted;
            data_0212ceb0[contacted->type].statusFlags |= 0x4000;
        }
    }
    GenericKnockback(e, em23_stateTable);
}

// Functions in this file: em23_init (0x0203fb88).

void em23_init(Entity *e) {
    e->action = 1;
    e->subtimer = Random();
    e->spriteSettings.b0 = 1;
    e->hitbox = data_020d2d98;
    e->direction = Random() & 0x1f;
    if (VARS(Vars_em23, e)->respawnDelay != 0) {
        VARS(Vars_em23, e)->respawnDelay = 0x258;
    }
    InitAnimationForceUpdate(e, 0);
}

// Functions in this file: em23_wait (0x0203fbe8), em23_move (0x0203fc5c).

void em23_wait(Entity *e) {
    Entity *target;
    if (VARS(Vars_em23_aim, e)->aimTarget != NULL) {
        target = EmGetAimPl();
        if (VARS(Vars_em23_aim, e)->aimTarget == target) {
            return;
        }
        e->action = 2;
        VARS(Vars_em23_aim, e)->aimTarget = target;
        e->direction = GetFacingDirection(e, target);
        return;
    }
    target = func_02084f98(e, 0x78, 0x50);
    VARS(Vars_em23_aim, e)->aimTarget = target;
    if (target == NULL) {
        return;
    }
    e->action = 2;
    e->direction = GetFacingDirection(e, target);
}

void em23_move(Entity *e) {
    if ((frameCounter & 7) == 0) {
        func_02086200(e, func_02084fd0(e, VARS(Vars_em23_aim, e)->aimTarget));
    }
    func_020847f8(e);
}

// Functions in this file: em23_vanish (0x0203fc98).

void em23_vanish(Entity *e) {
    e->spriteSettings.b0 ^= 1;
    e->timer--;
    if (e->timer == 0) {
        PutObjWork(e);
    }
}
