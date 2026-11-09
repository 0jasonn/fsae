#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/encnt.h"

// housha0att: like housha0, but also counts blocked cells of the two neighbour grids around the target cell. The slot is
// taken when the target cell itself is blocked (counts 2) or when two or more neighbours are blocked.
void housha0att(EncntEntry *e, u16 index) {
    u16 x;
    u16 y;
    u16 cell;
    u16 i;
    u16 blocked;

    if (e->taken != 0) {
        return;
    }
    x = (e->x + (trigTable[e->angle * 8] >> 4)) & 0x3ff;
    y = (e->y + (trigTable[e->angle * 8 + 0x40] >> 4)) & 0x3ff;
    cell = (x - mapState.x) >> 4 | ((y - mapState.y) >> 4) << 6;
    blocked = 0;
    if (data_0215afa4[cell] != 0 || data_02165fa8[cell] != 0) {
        blocked = 2;
    }
    for (i = 0; i < 4; i++) {
        if (data_02158fa0[cell + cellDeltaTable[i] + 0x2004] != 0 || data_02163fa4[cell + cellDeltaTable[i] + 0x2004] != 0) {
            blocked++;
        }
    }
    if (blocked >= 2) {
        e->taken = 1;
    } else {
        e->x = x;
        e->y = y;
    }
}
