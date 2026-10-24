#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Kinomi HUD display (module kinomi, second file). Original name from the debug build: kinomi_disp().

extern u8 data_0212c618[];
extern u8 data_021361a0[];
extern u16 data_020cf868[];

// Writes nine six-halfword rows (rows 5 to 13 of the screen block, 0x40 bytes apart, starting at block + 8) from the
// table data_020cf868, then sets data_0212c618[2].
ARM void kinomi_disp(void) {
    u8 *block;
    u16 *row;
    const u16 *table;
    s32 index;
    u8 i;

    block = data_021361a0 + (data_0212c618[3] << 11);
    table = data_020cf868;
    i = 0;
    do {
        index = ((i + 5) << 8) / 8;
        row = (u16 *)(block + 8) + index;
        row[0] = table[0];
        row[1] = table[1];
        row[2] = table[2];
        row[3] = table[3];
        row[4] = table[4];
        row[5] = table[5];
        table += 6;
        i++;
    } while (i < 9);
    data_0212c618[2] = 1;
}
