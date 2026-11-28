#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/wm/wm_system.h"

// WmClearFifoRecvFlag() (0x0201f2c4): clears bit 0 of the halfword at 0x02ffff96 (the ARM7's FIFO-receive flag) when set.
void WmClearFifoRecvFlag(void) {
    volatile u16 *flags = (volatile u16 *)0x02ffff96;
    u16 value = *flags;

    if (value & 1) {
        *flags = value & 0xfffe;
    }
}
