#include "engine/functions.h"
#include "global.h"
#include "enemy/em23.h"
#include "enemy/em23_5.h"

// Functions in this file: em23_wait (0x0203fbe8), em23_move (0x0203fc5c).

ARM void em23_wait(Entity *e) {
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

ARM void em23_move(Entity *e) {
    if ((frameCounter & 7) == 0) {
        func_02086200(e, func_02084fd0(e, VARS(Vars_em23_aim, e)->aimTarget));
    }
    func_020847f8(e);
}
