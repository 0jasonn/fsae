#include "sdk/os/os_vram_exclusive.h"

// Clears the VRAM exclusive-use bookkeeping.
void OSi_InitVramExclusive(void) {
    s32 i;
    data_02129c94 = 0;
    for (i = 0; i < 9; i++) {
        data_02129c98[i] = 0;
    }
}
