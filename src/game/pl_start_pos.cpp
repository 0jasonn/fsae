#include "engine/functions.h"
#include "global.h"
#include "actor/object/objdecls_f.h"

// 0x02054fe4 PlStartPosSet (original name, C linkage): places the entity at the start slot of its type;
// data_0212c84c holds the (x, y) cell of each of the 4 start slots (frame_load.h).

extern u8 data_0212c84c[];

void PlStartPosSet(Entity *e) {
    e->x.HALF.HI = (data_0212c84c[e->type * 2] << 4) | 8;
    e->y.HALF.HI = (data_0212c84c[e->type * 2 + 1] << 4) | 8;
}
