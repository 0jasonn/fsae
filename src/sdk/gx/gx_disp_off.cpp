#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/gx.h"
#include "sdk/pm/pm.h"

void GX_DispOff(void) {
    volatile u32 *dispcnt = (volatile u32 *)0x4000000;
    u32 value = *dispcnt;

    data_020dfb7c = 0;
    data_02129824 = (value & 0x30000) >> 16;
    *dispcnt = value & ~0x30000;
    PMi_SetDispOffCount();
}
