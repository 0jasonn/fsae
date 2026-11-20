#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/object/objdecls_f.h"

// 0x02054fe4 PlStartPosSet (original name, C linkage): places the entity at the start slot of its type;
// gameState.startCells (data_0212c84c) holds the (x, y) cell of each of the 4 start slots.


void PlStartPosSet(Entity *e) {
    e->x.HALF.HI = (gameState.startCells[e->type * 2] << 4) | 8;
    e->y.HALF.HI = (gameState.startCells[e->type * 2 + 1] << 4) | 8;
}
