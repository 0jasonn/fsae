#include "sdk/card/card_task.h"

// Resets the card ROM command and waits for the controller's refresh to finish.
void CARDi_RefreshRomCore(void) {
    volatile u32 *controlShadow;
    volatile u32 *romControl;
    u32 control;

    CARDi_SetRomOp(0xb5, 0);
    controlShadow = (volatile u32 *)0x02fffae0;
    romControl = (volatile u32 *)0x040001a4;
    control = *controlShadow;
    control &= ~0x07000000;
    control |= 0xa0000000;
    control &= ~0x1fff;
    *romControl = control;
    while ((*romControl & 0x80000000) != 0) {
    }
}
