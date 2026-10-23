#include "engine/functions.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"
#include "enemy/em0f_2.h"

ARM void em0f_wait(Entity *e) {
    if (--e->timer == 0) {
        e->unk_2e = 0;
        homingSet(e);
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_homingMove(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    vars->homingTimer--;
    if (vars->homingTimer != 0) {
        if (--e->timer == 0) {
            e->timer = 4;
            func_02086200(e, GetFacingDirection(e, vars->aimTarget));
        }
        spdchange(e);
        func_020847f8(e);
    } else {
        e->action = 7;
        e->timer = 0x3c;
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_homingMoveEnd(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    if (--e->timer == 0) {
        e->action = 8;
        e->speed = 0xc0;
        vars->attackMode = (vars->attackMode & 0xf) + 0x10;
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_move2center(Entity *e) {
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, 0x1f8, 0x1f8);
    func_020847f8(e);
    if ((u16)(e->x.HALF.HI - 0x1f7) <= 2) {
        if ((u16)(e->y.HALF.HI - 0x1f7) <= 2) {
            e->action = 9;
            e->timer = 0x3c;
        }
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_centerwait(Entity *e) {
    if (--e->timer == 0) {
        if (Random() & 1) {
            vacuumSet(e);
        } else {
            thunderSet(e);
        }
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_vacuumInit(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    e->z.WORD -= 0xb000;
    if (e->z.HALF.HI == -0x58) {
        e->action = 0xb;
        vars->homingTimer = 0x1e0;
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_vacuum(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    UpdateAnimationSingleFrame(e);
    if (vars->homingTimer != 0) {
        vars->homingTimer--;
        return;
    }
    if (vars->unk_7e != 0) {
        return;
    }
    e->action = 0xc;
    vars->unk_7d = 0;
    InitAnimationForceUpdate(e, 0);
}


ARM void em0f_vacuumEnd(Entity *e) {
    e->z.WORD += 0xb000;
    if (e->z.HALF.HI == -0x40) {
        e->action = 0xd;
        e->timer = 0xf0;
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_vacuumWait(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    if (--e->timer == 0) {
        if ((vars->attackMode & 0xf) != 0) {
            vars->attackMode &= 0xf0;
            homingSet(e);
        } else {
            vars->attackMode |= 1;
            if (e->health > 0x28) {
                if ((Random() & 7) < 3) {
                    thunderSet(e);
                } else {
                    homingSet(e);
                }
            } else {
                if ((Random() & 7) < 5) {
                    thunderSet(e);
                } else {
                    homingSet(e);
                }
            }
        }
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_thunder(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        e->action = 0xf;
        e->timer = 0xf0;
        InitAnimationForceUpdate(e, 0);
    }
}


ARM void em0f_thunderWait(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    if (--e->timer == 0) {
        if ((vars->attackMode & 0xf) != 0) {
            vars->attackMode &= 0xf0;
            homingSet(e);
        } else {
            vars->attackMode |= 1;
            if (e->health > 0x28) {
                if ((Random() & 7) < 3) {
                    vacuumSet(e);
                } else {
                    homingSet(e);
                }
            } else {
                if ((Random() & 7) < 5) {
                    vacuumSet(e);
                } else {
                    homingSet(e);
                }
            }
        }
    }
    UpdateAnimationSingleFrame(e);
}


ARM void em0f_piyori(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);

    UpdateAnimationSingleFrame(e);
    if (--vars->homingTimer == 0) {
        e->action = 3;
        e->unk_2e = 8;
        e->spriteSettings.b30 = 1;
        e->spriteSettings.b14 = 1;
        e->unk_5e.b0 = 3;
        InitAnimationForceUpdate(e, 2);
    }
}


ARM void homingMoveSet(Entity *e) {
    Vars_Em0f *vars = VARS(Vars_Em0f, e);
    u32 pick;
    u8 targetIndex;

    switch (data_0212c7c8.unk_0) {
        case 1:
            vars->aimTarget = data_0212ceb0[0].entity;
            break;
        case 2:
        case 3:
        case 4:
            pick = Random() % (data_0212c7c8.unk_0 - 1);
            targetIndex = (em0f_aimPlayerTable + vars->aimTarget->type * 3)[pick];
            vars->aimTarget = data_0212ceb0[targetIndex].entity;
            break;
    }
    e->direction = GetFacingDirection(e, vars->aimTarget);
    vars->dashCount = em0f_dashCountTable[Random() & 3];
}


