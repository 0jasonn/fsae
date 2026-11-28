#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"

// PMi_WaitVBlank() (0x0201c884): waits until the VBlank counter the ARM7 keeps at 0x02fffc3c changes.
void PMi_WaitVBlank(void) {
    volatile u32 start = *(volatile u32 *)0x02fffc3c;
    u32 now;

    do {
        now = *(volatile u32 *)0x02fffc3c;
    } while (start == now);
}
