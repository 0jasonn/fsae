#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"
#include "enemy/em1a.h"

// Actor em1a (original names from the debug build): Em1a, em1a_normal, em1a_damage, em1a_init,
// em1a_revivalwait, em1a_move, em1a_move_u, em1a_move_ur, em1a_move_r, em1a_move_dr, em1a_move_d,
// em1a_move_dl, em1a_move_l, em1a_move_ul, em1a_move_wait. em1a_getNextInfo is in the next unit.

ARM void Em1a(Entity *e) {
    if (data_0212c540.unk_2 > 1) {
        func_02084700(e);
    }
    em1a_actions[func_02084a30(e)](e);
}

ARM void em1a_normal(Entity *e) {
    em1a_normalActions[e->action](e);
}

ARM void em1a_damage(Entity *e) {
    Entity *set;
    Entity *child;
    Vars_Em1a *childVars;

    set = GetSetWork(0x20, 0xff, 0);
    if (set != NULL) {
        ObjPosCopy(e, set);
    }
    child = GetEnemyWork(0x1a);
    if (child != NULL) {
        childVars = VARS(Vars_Em1a, child);
        ObjPosCopy(e, child);
        child->x.HALF.HI = VARS(Vars_Em1a, e)->homeX;
        child->y.HALF.HI = VARS(Vars_Em1a, e)->homeY;
        child->type2 = e->type2;
        childVars->revivalTimer = 0x2d0;
    }
    PutObjWork(e);
}

ARM void em1a_init(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    e->subtimer = Random();
    e->unk_2e = 6;
    e->hitbox = em1a_hitbox;
    vars->homeX = e->x.HALF.HI;
    vars->homeY = e->y.HALF.HI;
    vars->infoPtr = GetInfoAdrs(e->areaIndex, e->type2);
    vars->infoBase = vars->infoPtr;
    em1a_getNextInfo(e);
    InitAnimationForceUpdate(e, 0);
    if (vars->revivalTimer != 0) {
        e->action = 1;
        e->statusFlags &= 0x7f;
    } else {
        e->action = 2;
        e->spriteSettings.b0 = 1;
    }
}

ARM void em1a_revivalwait(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    vars->revivalTimer--;
    if (vars->revivalTimer == 0) {
        e->action = 2;
        e->spriteSettings.b0 = 1;
        e->statusFlags |= 0x80;
        return;
    }
    if (vars->revivalTimer < 0x78) {
        e->spriteSettings.b0 ^= 1;
    }
}

ARM void em1a_move(Entity *e) {
    e->z.HALF.HI = em1a_bobTable[((frameCounter + e->subtimer) & 0x30) >> 4];
    UpdateAnimationSingleFrame(e);
    em1a_moveActions[e->subAction](e);
}

ARM void em1a_move_u(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    MoveDir(e);
    if (vars->targetY < e->y.HALF.HI) {
        return;
    }
    e->y.HALF.HI = vars->targetY;
    em1a_getNextInfo(e);
}

ARM void em1a_move_ur(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    MoveDir(e);
    if (vars->targetY < e->y.HALF.HI || vars->targetX > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = vars->targetX;
    e->y.HALF.HI = vars->targetY;
    em1a_getNextInfo(e);
}

ARM void em1a_move_r(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    MoveDir(e);
    if (vars->targetX > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = vars->targetX;
    em1a_getNextInfo(e);
}

ARM void em1a_move_dr(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    MoveDir(e);
    if (vars->targetY > e->y.HALF.HI || vars->targetX > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = vars->targetX;
    e->y.HALF.HI = vars->targetY;
    em1a_getNextInfo(e);
}

ARM void em1a_move_d(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    MoveDir(e);
    if (vars->targetY > e->y.HALF.HI) {
        return;
    }
    e->y.HALF.HI = vars->targetY;
    em1a_getNextInfo(e);
}

ARM void em1a_move_dl(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    MoveDir(e);
    if (vars->targetY > e->y.HALF.HI || vars->targetX < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = vars->targetX;
    e->y.HALF.HI = vars->targetY;
    em1a_getNextInfo(e);
}

ARM void em1a_move_l(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    MoveDir(e);
    if (vars->targetX < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = vars->targetX;
    em1a_getNextInfo(e);
}

ARM void em1a_move_ul(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);

    MoveDir(e);
    if (vars->targetY < e->y.HALF.HI || vars->targetX < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = vars->targetX;
    e->y.HALF.HI = vars->targetY;
    em1a_getNextInfo(e);
}

ARM void em1a_move_wait(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    em1a_getNextInfo(e);
}
