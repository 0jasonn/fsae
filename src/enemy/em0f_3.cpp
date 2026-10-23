#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"
#include "enemy/em0f_2.h"

ARM void vacuumSet(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    e->action = 0xa;
    vars->unk_7d = 1;
    vars->attackMode = (vars->attackMode & 0xf) + 0x20;
    InitAnimationForceUpdate(e, 1);
}


ARM void thunderSet(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);
    Entity *tama;

    e->action = 0xe;
    vars->attackMode = (vars->attackMode & 0xf) + 0x30;
    tama = GetTamaWork(0xa);
    if (tama != NULL) {
        tama->parent = e;
    }
    InitAnimationForceUpdate(e, 4);
}


ARM void homingSet(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    e->action = 6;
    e->timer = 4;
    e->speed = 0;
    vars->attackMode &= 0xf;
    vars->homingTimer = em0f_homingTimerTable[Random() & 3];
    homingMoveSet(e);
}


