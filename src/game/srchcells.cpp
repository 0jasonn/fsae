#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/decls_b2.h"

// Functions in this file (module srchCells, original name from the debug build): srchCells
//   (srchCells(unsigned short, unsigned short, unsigned short))

extern "C" u16 *srchCells(u16 start, u16 width, u16 height);

// srchCells (0x0204e3e0): allocates a list of width * height cell ids (count in the first halfword). Each row holds
// the ids from the start id on, and the row starts 64 - width ids further on. The list is then shuffled.
ARM u16 *srchCells(u16 start, u16 width, u16 height) {
    u16 *list;
    u16 count;
    u16 value;
    u16 i;
    u16 *out;
    u16 k;

    count = (u16)(width * height);
    list = (u16 *)zMalloc((u16)((count + 1) << 1));
    if (list == NULL) {
        return NULL;
    }
    list[0] = count;
    out = list + 1;
    value = start;
    for (i = 0; i < height; i++) {
        for (k = 0; k < width; k++) {
            *out = value;
            out++;
            value++;
        }
        value = value + (u16)(64 - width);
    }
    shuffledata(list + 1, count);
    return list;
}
