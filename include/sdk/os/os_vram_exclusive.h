#ifndef SDK_OS_OS_VRAM_EXCLUSIVE_H
#define SDK_OS_OS_VRAM_EXCLUSIVE_H

// TwlSDK OS exclusive use of the VRAM banks between the processors.
#include "types.h"

extern u32 data_02129c94;       // VRAM exclusive owner flag word
extern u16 data_02129c98[9];    // VRAM exclusive owner (lock ID) of each bank

extern "C" {
void OSi_InitVramExclusive(void);
u32 OSi_TryLockVram(u16 banks, u16 lockId); // not decompiled yet; 0 when a bank is held by another lock ID
}

#endif
