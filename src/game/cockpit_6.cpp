#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module cockpit, original names from the debug build):
//   cockpit_write_rupee (write_rupee), rupee_disp

// Writes the decimal digits of value, count of them from the right, to the tile map: two rows of tiles (the second 0x40
// bytes below the first), each digit gets its own tile (0x20 + digit and 0x40 + digit, OR-ed with the flags).
ARM void cockpit_write_rupee(u16 *dst, u32 value, u8 count, u16 flags) {
    u32 digit;

    if (count == 0) {
        return;
    }
    do {
        digit = value % 10;
        dst[0] = (digit + 0x20) | flags;
        dst[0x20] = (digit + 0x40) | flags;
        value = value / 10;
        count -= 1;
        dst -= 1;
    } while (count != 0);
}
