#include "engine/functions.h"
#include "global.h"

// SetTblSetWorks (0x02076804): walks a table of 5-byte entries {kind, a, b, x, y} ended by kind == 0, fetches the
// set work of each entry with GetSetWork and places it at (x, y). Returns FALSE as soon as one is missing.
BOOL SetTblSetWorks(const u8 *table) {
    const u8 *entry = table;
    while (entry[0] != 0) {
        Entity *work = GetSetWork(entry[0], entry[1], entry[2]);
        if (work == NULL) return FALSE;
        work->x.HALF.HI = entry[3];
        work->y.HALF.HI = entry[4];
        entry += 5;
    }
    return TRUE;
}
