#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Kinomi HUD display (module kinomi, second file). Original name from the debug build: kinomi_disp().

extern u8 data_0212c618[];
extern u8 data_021361a0[];
extern u16 data_020cf868[];

// Writes nine six-halfword rows (rows 5 to 13 of the screen block, 0x40 bytes apart, starting at block + 8) from the
// table data_020cf868, then sets data_0212c618[2].
void kinomi_disp(void) {
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

// Functions in this file (module kinomi, original names from the debug build):
//   kinomi_write (kinomi_write()), kinomi_write_sub (kinomi_write_sub(unsigned short*, unsigned char, unsigned short))

// Three 2-bit kinomi modes kept in the byte at +0x3e of the block that data_0212c53c points to.
typedef struct KinomiModeBits {
    u8 modeLow : 2;  // bits 0..1
    u8 modeMid : 2;  // bits 2..3
    u8 modeHigh : 2; // bits 4..5
    u8 rest : 2;
} KinomiModeBits;

#define KINOMI_MODES(p) ((KinomiModeBits *)((p) + 0x3e))

void kinomi_write_sub(u16 *dst, u8 mode, u16 value);

// kinomi_write (0x02027930): three kinomi tile pairs in the block selected by data_0212c618[3] (0x800 bytes each). Each
// pair takes its mode from one of the 2-bit fields of the byte at +0x3e of the block pointed to by data_0212c53c.
void kinomi_write(void) {
    kinomi_write_sub((u16 *)(data_021361a0 + (data_0212c618[3] << 11) + 0x8e + 0x100), KINOMI_MODES(data_0212c53c)->modeLow, 0x2e);
    kinomi_write_sub((u16 *)(data_021361a0 + (data_0212c618[3] << 11) + 0x4e + 0x200), KINOMI_MODES(data_0212c53c)->modeMid, 0x102d);
    kinomi_write_sub((u16 *)(data_021361a0 + (data_0212c618[3] << 11) + 0xe + 0x300), KINOMI_MODES(data_0212c53c)->modeHigh, 0x202c);
}

// Writes two tile words at dst: mode 0 blanks both with tile 0xc, mode 1 writes value then 0xc, any other mode writes
// value twice.
void kinomi_write_sub(u16 *dst, u8 mode, u16 value) {
    switch (mode) {
    case 0:
        dst[0] = 0xc;
        dst[1] = 0xc;
        return;
    case 1:
        dst[0] = value;
        dst[1] = 0xc;
        return;
    default:
        dst[0] = value;
        dst[1] = value;
        return;
    }
}
