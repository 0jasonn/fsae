#include "global.h"
#include "types.h"
#include "sdk/mi/mi_wram.h"

void MI_SetWramBank(u32 bank) {
    *(volatile u8 *)0x04000247 = bank;
}
