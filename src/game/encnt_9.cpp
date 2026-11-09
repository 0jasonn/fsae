#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/encnt.h"

// housha0: moves a free spawn slot one step along its direction (angle 0..63, trigTable steps in 1/16). The slot is taken
// when the new position hits a blocked cell of the two occupancy grids (relative to the map origin), otherwise it moves.
void housha0(EncntEntry *e, u16 index) {
    u16 x;
    u16 y;
    u16 cell;

    if (e->taken != 0) {
        return;
    }
    x = (e->x + (trigTable[e->angle * 8] >> 4)) & 0x3ff;
    y = (e->y + (trigTable[e->angle * 8 + 0x40] >> 4)) & 0x3ff;
    cell = (x - mapState.x) >> 4 | ((y - mapState.y) >> 4) << 6;
    if (data_0215afa4[cell] != 0 || data_02165fa8[cell] != 0) {
        e->taken = 1;
    } else {
        e->x = x;
        e->y = y;
    }
}
