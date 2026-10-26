#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// plmove (0x0206cc9c): the actor moves with the player-hit test against each of the four players. Vars hold the
// base point (0x78, 0x7a) and the half-range (0x7c, 0x7e) of the actor.
typedef struct Vars_PlMove {
    u8 unk_00[0x78];
    s16 baseX;
    s16 baseY;
    u16 rangeX;
    u16 rangeY;
} Vars_PlMove;

extern "C" void getarea(Entity *e);
extern "C" int func_02086120(Entity *e);

// plmove (0x0206cc9c)
ARM void plmove(Entity *e) {
    Vars_PlMove *vars;
    s32 x;
    s32 y;

    getarea(e);
    vars = VARS(Vars_PlMove, e);
    switch (e->type) {
    case 0:
    case 3:
        x = vars->baseX;
        y = vars->baseY;
        break;
    case 1:
        x = (s16)((u16)vars->baseX - vars->rangeX);
        y = vars->baseY;
        break;
    case 2:
        x = vars->baseX;
        y = (s16)((u16)vars->baseY - vars->rangeY);
        break;
    }
    if (func_02086120(data_0212ceb0[0].entity) != 0) {
        if ((data_0212ceb0[0].entity->layer & e->layer) >> 14 != 0) {
            if (vars->rangeX >= (u16)(data_0212ceb0[0].entity->x.HALF.HI - x)) {
                if (vars->rangeY >= (u16)(data_0212ceb0[0].entity->y.HALF.HI - y)) {
                    func_020852f8(data_0212ceb0[0].entity, e->speed, e->direction);
                }
            }
        }
    }
    if (func_02086120(data_0212ceb0[1].entity) != 0) {
        if ((data_0212ceb0[1].entity->layer & e->layer) >> 14 != 0) {
            if (vars->rangeX >= (u16)(data_0212ceb0[1].entity->x.HALF.HI - x)) {
                if (vars->rangeY >= (u16)(data_0212ceb0[1].entity->y.HALF.HI - y)) {
                    func_020852f8(data_0212ceb0[1].entity, e->speed, e->direction);
                }
            }
        }
    }
    if (func_02086120(data_0212ceb0[2].entity) != 0) {
        if ((data_0212ceb0[2].entity->layer & e->layer) >> 14 != 0) {
            if (vars->rangeX >= (u16)(data_0212ceb0[2].entity->x.HALF.HI - x)) {
                if (vars->rangeY >= (u16)(data_0212ceb0[2].entity->y.HALF.HI - y)) {
                    func_020852f8(data_0212ceb0[2].entity, e->speed, e->direction);
                }
            }
        }
    }
    if (func_02086120(data_0212ceb0[3].entity) != 0) {
        if ((data_0212ceb0[3].entity->layer & e->layer) >> 14 != 0) {
            if (vars->rangeX >= (u16)(data_0212ceb0[3].entity->x.HALF.HI - x)) {
                if (vars->rangeY >= (u16)(data_0212ceb0[3].entity->y.HALF.HI - y)) {
                    func_020852f8(data_0212ceb0[3].entity, e->speed, e->direction);
                }
            }
        }
    }
}
