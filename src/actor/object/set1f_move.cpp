#include "engine/functions.h"
#include "global.h"
#include "actor/object/set1f.h"
#include "actor/object/object_handlers.h"
#include "engine/irq.h"

// 0x0205a050 set1f_move (original name): bobs the z position every 8th frame.

void set1f_move(Entity *e) {
    if ((frameState.frameCount & 7) == 0) {
        e->timer++;
        e->z.HALF.HI = set1f_zTable[e->timer & 7] - 8;
    }
}
