#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module cg, original names from the debug build): SetCgColor (SetCgColor(unsigned long, unsigned long)),
// SetDataVBlank (SetDataVBlank(void const*, void*, unsigned long))

typedef struct VBlankEntry {
    const void *src;
    void *dst;
    u32 size;
} VBlankEntry;

extern const u8 *data_020f2a18;  // colour adjust table (u16 entries), NULL for none
extern u16 data_021355a0[];      // colour per index
extern u32 em2f_mapFlag;         // bit set of the indices with a colour (named em2f_mapFlag in symbols.txt)
extern u8 data_02134890;         // number of VBlank entries
extern VBlankEntry data_02134894[2];

// SetCgColor (0x02029d0c): stores colour at index. With a colour adjust table, the colour is the OR of three table entries
// (5-bit fields 0..4, 5..9 and 10..14 of colour, the second and third table halves are offset by 0x20 and 0x40).
ARM void SetCgColor(u32 index, u32 color) {
    const u16 *table;

    table = (const u16 *)data_020f2a18;
    if (table != NULL) {
        color = table[color & 0x1f] | table[((color & 0x3e0) >> 5) + 0x20] | table[((color & 0x7c00) >> 10) + 0x40];
    }
    data_021355a0[index] = color;
    em2f_mapFlag |= 1 << (index >> 4);
}

// SetDataVBlank (0x02029d88): queues a VBlank transfer (source, destination, size) unless two are already queued.
ARM void SetDataVBlank(const void *src, void *dst, u32 size) {
    u8 count;

    count = data_02134890;
    if (count >= 2) {
        return;
    }
    data_02134894[count].src = src;
    data_02134894[count].dst = dst;
    data_02134894[count].size = size;
    data_02134890 = count + 1;
}
