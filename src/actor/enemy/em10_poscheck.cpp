#include "engine/functions.h"
#include "global.h"

// poscheck (0x0203afd0): true when the coordinate that matters for the facing direction (x for directions with bit 3, y
// otherwise) is centred on its tile (low nibble 8). While moving faster than 0x100 a nibble of 7..9 is enough and the
// coordinate is snapped to the tile centre.
int poscheck(Entity *e) {
    s16 *pos;
    s16 value;
    u8 nibble;

    if (e->direction & 8) {
        pos = &e->x.HALF.HI;
    } else {
        pos = &e->y.HALF.HI;
    }
    value = *pos;
    nibble = value & 0xf;
    if (e->speed <= 0x100) {
        if (nibble == 8) {
            return 1;
        }
    } else if (nibble >= 7 && nibble <= 9) {
        *pos = (value & 0x3f0) + 8;
        return 1;
    }
    return 0;
}
