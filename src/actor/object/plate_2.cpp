#include "engine/functions.h"
#include "actor/object/plate.h"

void plate_posY_set(Entity *e) {
    s16 screenY = e->parent->y.HALF.HI - mapState.unk_22;

    if (screenY < 0x10) {
        e->y.HALF.HI = 0x10;
        if (e->unk_23 >= 7) {
            return;
        }
        InitAnimationForceUpdate(e, e->unk_23 + 5);
    } else {
        e->y.HALF.HI = screenY - 0x28;
        if (e->y.HALF.HI < 0x10) {
            e->y.HALF.HI = 0x10;
        }
        if (e->y.HALF.HI > 0x90) {
            e->y.HALF.HI = 0x90;
        }
    }
}
