#include "engine/functions.h"
#include "global.h"
#include "engine/misc.h"
#include "game/bginit.h"

// Functions in this file: BgInit (0x02021a10).

void BgInit(void) {
    u16 i;
    u32 *slot;

    *(u16 **)data_02158fa0 = &data_0212c77c;
    data_0212c77c = *(const u16 *)(data_020ce4d0 + 0x20);
    *(u16 **)data_02163fa4 = &data_0212c770;
    data_0212c770 = *(const u16 *)(data_020ce4d0 + 0x22);
    slot = data_02134a68;
    for (i = 0; i < 8; i++) {
        *slot = 0;
        slot += 2;
    }
    displayState.displayFlags |= 0x600;
}
