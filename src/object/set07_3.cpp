#include "engine/functions.h"
#include "global.h"

// Set07 actor, cell helper (module set07). Address -> name:
//   0x02061b88 blockRewCell (original name)

ARM void blockRewCell(u16 cell, Entity *e) {
    if ((e->layer >> 14) != 2) {
        if (e->direction & 8) {
            RewCell(0x51, cell, e->layer);
        } else {
            RewCell(0x50, cell, e->layer);
        }
    } else {
        if (e->direction & 8) {
            RewCell(0x7a, cell, e->layer);
        } else {
            RewCell(0x79, cell, e->layer);
        }
    }
}
