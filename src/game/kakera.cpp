#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Kakera HUD functions (module kakera). Original name from the debug build: kakera_write(unsigned char const*).

extern u8 data_0212c618[];
extern u8 data_021361a0[];
extern u16 data_020cf842[];

// Writes four kakera tiles: each source byte selects a 6-halfword tile pattern, written as a 3 by 2 block into the
// screen block of the current cockpit page (block at 0x1a8, rows 0x40 halfwords apart).
ARM void kakera_write(const u8 *kakera) {
    u16 *dst;
    u8 count;
    u8 index;
    const u16 *pattern;

    dst = (u16 *)(data_021361a0 + (data_0212c618[3] << 11) + 0x1a8);
    count = 4;
    do {
        index = *kakera++;
        pattern = data_020cf842 + index * 6;
        dst[0] = pattern[0];
        dst[1] = pattern[1];
        dst[2] = pattern[2];
        dst[0x20] = pattern[3];
        dst[0x21] = pattern[4];
        dst[0x22] = pattern[5];
        dst += 0x40;
        count--;
    } while (count != 0);
}
