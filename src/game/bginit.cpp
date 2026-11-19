#include "engine/functions.h"
#include "global.h"
#include "engine/misc.h"
#include "game/bginit.h"

// Functions in this file: BgInit (0x02021a10).

void BgInit(void) {
    u16 i;
    u32 *slot;

    data_02158fa0.disp = &displayState.bg[2];
    data_02158fa0.disp->cnt = *(const u16 *)(data_020ce4d0 + 0x20);
    data_02163fa4.disp = &displayState.bg[1];
    data_02163fa4.disp->cnt = *(const u16 *)(data_020ce4d0 + 0x22);
    slot = data_02134a68;
    for (i = 0; i < 8; i++) {
        *slot = 0;
        slot += 2;
    }
    displayState.displayFlags |= 0x600;
}
