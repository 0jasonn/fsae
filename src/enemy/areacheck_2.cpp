#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"

// Functions in this file (original name areacheck):
//   areacheck

// Areacheck: 0 when one of the players (in table order, stopping at the first missing one) is inside the box, else 1.
// The box is the one around e: x offset 0x18 with width 0x30, y offset 0x12 with height 0x24.
ARM BOOL areacheck(Entity *e) {
    Entity *target;
    s32 dx;
    s32 dy;

    target = data_0212ceb0[0].entity;
    dx = target->x.HALF.HI - e->x.HALF.HI + 0x18;
    if ((u32)dx <= 0x30) {
        dy = target->y.HALF.HI - e->y.HALF.HI + 0x12;
        if ((u32)dy <= 0x24) {
            return 0;
        }
    }
    target = data_0212ceb0[1].entity;
    if (target != NULL) {
        dx = target->x.HALF.HI - e->x.HALF.HI + 0x18;
        if ((u32)dx <= 0x30) {
            dy = target->y.HALF.HI - e->y.HALF.HI + 0x12;
            if ((u32)dy <= 0x24) {
                return 0;
            }
        }
        target = data_0212ceb0[2].entity;
        if (target != NULL) {
            dx = target->x.HALF.HI - e->x.HALF.HI + 0x18;
            if ((u32)dx <= 0x30) {
                dy = target->y.HALF.HI - e->y.HALF.HI + 0x12;
                if ((u32)dy <= 0x24) {
                    return 0;
                }
            }
            target = data_0212ceb0[3].entity;
            if (target != NULL) {
                dx = target->x.HALF.HI - e->x.HALF.HI + 0x18;
                if ((u32)dx <= 0x30) {
                    dy = target->y.HALF.HI - e->y.HALF.HI + 0x12;
                    if ((u32)dy <= 0x24) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
