#include "engine/functions.h"
#include "game/fade_native.h"
#include "global.h"

// write_* (0x020470e8 to 0x02047450): cell writes and the native init routines that call them.
// write_native_init_047450 is a bare return; named write_native_init_047450.

// Writes x and y into the two halves of a cell position pair (rewrite with weight 0x4000).
ARM void write_cell(u16 *pos, u16 x, u16 y) {
    RewCellOne(x, pos[0], 0x4000);
    RewCellOne(y, pos[1], 0x4000);
}

ARM void write_native_init_04711c(u8 param) {
    if (Random() & 1) {
        write_cell(cellPos_c0fe, 0x447, 0x43e);
    } else {
        write_cell(cellPos_c102, 0x447, 0x43e);
    }
    switch (Random() % 3) {
    case 0:
        write_cell(cellPos_c106, 0x447, 0x43e);
        break;
    case 1:
        write_cell(cellPos_c10a, 0x447, 0x43e);
        break;
    case 2:
        write_cell(cellPos_c10e, 0x447, 0x43e);
        break;
    }
    if (Random() & 1) {
        write_cell(cellPos_c112, 0x460, 0x455);
    } else {
        write_cell(cellPos_c116, 0x447, 0x43e);
    }
}

ARM void write_native_init_0471f8(u8 param) {
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_445d, param);
    } else {
        RandomBlockSet(nativeInitList_4458, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_4462, param);
    } else {
        RandomBlockSet(nativeInitList_4467, param);
    }
}

ARM void write_native_init_04725c(u8 param) {
    if (Random() & 1) {
        MultiEventSet(eventList_e32a, 0, 0, param);
    } else {
        MultiEventSet(eventList_e334, 0, 0, param);
    }
    if (Random() & 1) {
        MultiEventSet(eventList_e2f8, 0, 0, param);
    } else {
        MultiEventSet(eventList_e302, 0, 0, param);
    }
    if (Random() & 1) {
        MultiEventSet(eventList_e320, 0, 0, param);
    } else {
        MultiEventSet(eventList_e33e, 0, 0, param);
    }
    if (Random() & 1) {
        MultiEventSet(eventList_e316, 0, 0, param);
    } else {
        MultiEventSet(eventList_e30c, 0, 0, param);
    }
}

ARM void write_native_init_047334(u8 param) {
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_f23a, param);
    } else {
        RandomBlockSet(nativeInitList_f243, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_f240, param);
    } else {
        RandomBlockSet(nativeInitList_f23d, param);
    }
}

ARM void write_native_init_047398(u8 param) {
    switch (Random() % 3) {
    case 0:
        RandomBlockSet(nativeInitList_f7c9, param);
        break;
    case 1:
        RandomBlockSet(nativeInitList_f7cc, param);
        break;
    case 2:
        RandomBlockSet(nativeInitList_f7c6, param);
        break;
    }
}

ARM void write_native_init_047414(u8 param) {
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_fb76, param);
    } else {
        RandomBlockSet(nativeInitList_446c, param);
    }
}

ARM void write_native_init_047450(u8 param) {
}
