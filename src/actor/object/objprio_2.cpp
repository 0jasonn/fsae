#include "engine/functions.h"
#include "actor/object/objprio_2.h"
#include "global.h"

// ObjJumpPrioCheck (0x0204fe54): sets the sprite priority bits from the map cells around a jumping entity.
// Returns 1 when the cell above is solid (and not the 0x4a2 tile), otherwise 0.
int ObjJumpPrioCheck(Entity *e) {
    if ((e->layer & 0x8000) == 0) {
        int cell = func_02083c8c(e->x.HALF.HI, (s16)(e->y.HALF.HI - 4), 0x8000);
        if (cell != 0) {
            if (cell != 0x4a2) {
                e->spriteSettings.b30 = 2;
                e->spriteSettings.b14 = e->spriteSettings.b30;
                return 1;
            }
        } else {
            u32 cellBelow = func_02083c8c(e->x.HALF.HI, (s16)(e->y.HALF.HI + 0x10), 0x4000);
            if (func_02083e54(cellBelow) == 0x4009 || (cellBelow >= 0x109 && cellBelow <= 0x10c)) {
                e->spriteSettings.b30 = 2;
                e->spriteSettings.b14 = e->spriteSettings.b30;
                return 0;
            } else {
                e->spriteSettings.b30 = 1;
                e->spriteSettings.b14 = e->spriteSettings.b30;
                return 0;
            }
        }
    }
    return 0;
}
