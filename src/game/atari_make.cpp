#include "engine/functions.h"
#include "engine/bg_buff.h"
#include "engine/map_state.h"

// Functions in this file (original names from the debug build): AtariMake

// AtariMake() (0x02057344): builds the collision ("atari") attributes of both BG layers: every cell's attribute is
// looked up through the layer's cell map from its screen entry (data_02171e0c maps a cell to its attribute), then the
// column at the map's right edge and column 0x3f, and the row at the map's bottom edge and row 0x3f, are walled off
// with 0xff.
void AtariMake(void) {
    u8 *cellA = data_02158fa0.attr;
    u8 *cellB = data_02163fa4.attr;
    u16 *cellMapA = data_02158fa0.cellMap;
    u16 *cellMapB = data_02163fa4.cellMap;
    u16 *screenA = data_02158fa0.screen;
    u16 *screenB = data_02163fa4.screen;
    u8 *edgeA;
    u8 *edgeB;
    u16 n;

    for (n = 0; n < 0x1000; n++) {
        *cellA++ = data_02171e0c[cellMapA[*screenA++]];
        *cellB++ = data_02171e0c[cellMapB[*screenB++ & 0x7fff]];
    }
    cellA = data_02158fa0.attr + (mapState.limitX >> 4);
    cellB = data_02163fa4.attr + (mapState.limitX >> 4);
    edgeA = &data_02158fa0.attr[0x3f];
    edgeB = &data_02163fa4.attr[0x3f];
    for (n = 0; n < 0x40; n++) {
        *cellA = 0xff;
        cellA += 0x40;
        *cellB = 0xff;
        cellB += 0x40;
        *edgeA = 0xff;
        edgeA += 0x40;
        *edgeB = 0xff;
        edgeB += 0x40;
    }
    cellA = data_02158fa0.attr + ((mapState.limitY & 0xfff0) << 2);
    cellB = data_02163fa4.attr + ((mapState.limitY & 0xfff0) << 2);
    edgeA = &data_02158fa0.attr[0xfc0];
    edgeB = &data_02163fa4.attr[0xfc0];
    for (n = 0; n < 0x40; n++) {
        *cellA++ = 0xff;
        *cellB++ = 0xff;
        *edgeA++ = 0xff;
        *edgeB++ = 0xff;
    }
}
