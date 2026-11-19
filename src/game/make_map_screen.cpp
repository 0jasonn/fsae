#include "engine/functions.h"
#include "game/make_map_screen.h"

// MakeMapScreen (0x0202382c): expands a layer's screen block (64x64 cell entries) into the map screen. Every cell
// entry selects four 16-bit tile values (2x2) from the buffer's tile data, written to two consecutive rows of the
// 128 wide map (the second row is 0x80 entries further).
void MakeMapScreen(u16 *map, BG_BUFF_ *buffer) {
    u16 *screen = buffer->screen;
    u16 row;
    u16 group;
    u16 *tile;

    for (row = 0; row < 0x40; row++) {
        for (group = 0; group < 0x10; group++) {
            tile = (u16 *)buffer->unk_7004 + (screen[0] << 2);
            map[0] = tile[0];
            map[1] = tile[1];
            map[0x80] = tile[2];
            map[0x81] = tile[3];
            tile = (u16 *)buffer->unk_7004 + (screen[1] << 2);
            map[2] = tile[0];
            map[3] = tile[1];
            map[0x82] = tile[2];
            map[0x83] = tile[3];
            tile = (u16 *)buffer->unk_7004 + (screen[2] << 2);
            map[4] = tile[0];
            map[5] = tile[1];
            map[0x84] = tile[2];
            map[0x85] = tile[3];
            tile = (u16 *)buffer->unk_7004 + (screen[3] << 2);
            map[6] = tile[0];
            map[7] = tile[1];
            map[0x86] = tile[2];
            map[0x87] = tile[3];
            screen += 4;
            map += 8;
        }
        map += 0x80;
    }
}
