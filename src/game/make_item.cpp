#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module make_item, original names from the debug build):
//   make_item_color, make_item_color_2p, make_item_char, make_item_char_2p

// make_item_color (0x02027a10): sets the palette bank (bits 12..15) of the item tile word at data_0212c4a0 + 0xc from the
// item's colour table entry. Item 7 becomes 4 when the byte at +0xe is 2, otherwise it stays 7.
ARM void make_item_color(void) {
    u8 colorIndex;

    colorIndex = data_0212c618[0xc];
    if (colorIndex == 7) {
        colorIndex = (data_0212c618[0xe] == 2) ? 4 : 7;
    }
    *(u16 *)(data_0212c4a0 + 0xc) = (*(u16 *)(data_0212c4a0 + 0xc) & ~0xf000) | (((u32)data_020cf81c[colorIndex] << 28) >> 16);
}

// make_item_color_2p (0x02027a64): the same for the second player's item, bytes +0x2c and +0x2d, word at +0x14.
ARM void make_item_color_2p(void) {
    u8 colorIndex;

    colorIndex = data_0212c618[0x2c];
    if (colorIndex == 7) {
        colorIndex = (data_0212c618[0x2d] == 2) ? 4 : 7;
    }
    *(u16 *)(data_0212c4a0 + 0x14) = (*(u16 *)(data_0212c4a0 + 0x14) & ~0xf000) | (((u32)data_020cf81c[colorIndex] << 28) >> 16);
}

// make_item_char (0x02027ab8): when the item index at +0xc is not 0, copies 0x80 bytes of item graphics to 0x06405d00.
// The graphics come from Zelda resource 0x287 when the state byte at 0x8e is 1 or 4, otherwise from 0xa1, offset by the
// table entry of the item index.
ARM void make_item_char(void) {
    u8 *graphics;
    s32 useAltResource;

    if (data_0212c618[0xc] == 0) {
        return;
    }
    useAltResource = data_0212c7c8[0x8e] == 1 || data_0212c7c8[0x8e] == 4;
    if (useAltResource) {
        graphics = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x287);
    } else {
        graphics = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0xa1);
    }
    func_020845b0(0x6405d00, graphics + *data_020f253c[data_0212c618[0xc]], 0x80);
}

// make_item_char_2p (0x02027b44): the same for the second player, index at +0x2c, destination 0x06405d80.
ARM void make_item_char_2p(void) {
    u8 *graphics;
    s32 useAltResource;

    if (data_0212c618[0x2c] == 0) {
        return;
    }
    useAltResource = data_0212c7c8[0x8e] == 1 || data_0212c7c8[0x8e] == 4;
    if (useAltResource) {
        graphics = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x287);
    } else {
        graphics = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0xa1);
    }
    func_020845b0(0x6405d80, graphics + *data_020f253c[data_0212c618[0x2c]], 0x80);
}
