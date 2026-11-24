#include "engine/functions.h"
#include "sdk/card/card_task.h"

extern u8 data_020de6f0[];
extern u8 data_0218aa08[];

void *CARDi_GetDmaInterface(u32 mode) {
    void *interface = NULL;
    u32 secondary;

    if ((mode & 0x10) != 0) {
        secondary = 1;
    } else {
        secondary = 0;
    }

    mode &= ~0x10;
    if (mode <= 3) {
        interface = data_020de6f0;
        if (secondary != 0) {
            interface = data_0218aa08;
        }
    }
    return interface;
}
