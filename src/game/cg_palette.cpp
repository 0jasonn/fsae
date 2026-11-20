#include "engine/functions.h"

#include "engine/em2f_map_flag.h"
extern u16 *data_020f2a18; // colour translation table (3 x 32 entries: red, green, blue), NULL when unused
#include "engine/palette_buff.h"

// CgPalletSet (0x02029c60): copies `count` palette slots starting at `slot` into the palette buffer, translating every
// colour through the colour table when there is one, and marks the slots for upload.
void CgPalletSet(u16 *source, u32 slot, u32 count) {
    u32 mask;
    u32 remaining;
    u16 *table;
    u16 *dest;
    u32 bytes;

    mask = 1 << slot;
    remaining = count;
    while (--remaining != 0) {
        mask |= mask << 1;
    }
    em2f_mapFlag |= mask;
    table = data_020f2a18;
    dest = data_021355a0 + slot * 16;
    bytes = count * 32;
    if (table != NULL) {
        do {
            u16 color = *source++;
            bytes -= 2;
            *dest = (table[color & 0x1f] | table[0x20 + ((color & 0x3e0) >> 5)]) | table[0x40 + ((color & 0x7c00) >> 10)];
            dest++;
        } while (bytes != 0);
    } else {
        MIi_CpuCopyFast(source, dest, bytes);
    }
}
