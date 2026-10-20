#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpitdata.h"

// Functions in this file (no original names; provisional names from their behaviour):
//   Cockpit_GetGfxAddr -> Cockpit_GetGfxAddr
//   Cockpit_GetTableByte -> Cockpit_GetTableByte


// Graphics address for the cockpit item index: the cell block of the current state plus the offset of the index.
ARM u8 *Cockpit_GetGfxAddr(s32 index) {
    u8 *block;
    s32 isBig = 1;

    if (data_0212c7c8[0x8e] != 1 && data_0212c7c8[0x8e] != 4) {
        isBig = 0;
    }
    if (isBig) {
        block = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x287);
    } else {
        block = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0xa1);
    }
    return block + *data_020f253c[index];
}

// Byte of the cockpit table at data_020cf81c for the index.
ARM u8 Cockpit_GetTableByte(s32 index) {
    return data_020cf81c[index];
}
