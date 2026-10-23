#include "engine/functions.h"
#include "global.h"
#include "object/warphole.h"

// Warp hole actor, second unit (module warphole). Address -> name:
//   0x0205e05c pos_copy (original name)
//   (warphole_wait2 at 0x0205e078 and warphole_exit at 0x0205e114 are in the next units)

ARM void pos_copy(Entity *src, Entity *dst) {
    dst->x.WORD = src->x.WORD;
    dst->y.WORD = src->y.WORD;
    dst->z.HALF.HI = 0;
}
