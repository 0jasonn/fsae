#include "engine/functions.h"
#include "global.h"

// Set4e actor, third unit (module set4e), with kanaamiRew (contiguous). Address -> name:
//   0x0205e714 set4e_move (original name)
//   0x0205e758 kanaamiRew (original name): rewrites a 2x2 block of cells starting at index
//   (set4e_init at 0x0205e63c is in the previous unit)

void kanaamiRew(Entity *e, u16 index); // 0x0205e758, not yet in functions.h

void set4e_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        kanaamiRew(e, 0xcd);
        PutObjWork(e);
        return;
    }
    if (e->frame & 1) {
        EnqueueSFX(0x91);
    }
}

#include "engine/map_state.h"

#define KANAAMI_CELL(dx, dy)                                                                              \
    ((u16)(((e->x.HALF.HI + (dx) - mapState.originX) >> 4) | (((e->y.HALF.HI + (dy) - mapState.originY) >> 4) << 6)))

void kanaamiRew(Entity *e, u16 index) {
    RewCell(index, KANAAMI_CELL(-0x10, -0x10), 0x8000);
    RewCell((u16)(index + 1), KANAAMI_CELL(0, -0x10), 0x8000);
    RewCell((u16)(index + 2), KANAAMI_CELL(-0x10, 0), 0x8000);
    RewCell((u16)(index + 3), KANAAMI_CELL(0, 0), 0x8000);
}
