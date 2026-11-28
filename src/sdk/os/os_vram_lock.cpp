#include "global.h"
#include "types.h"
#include "sdk/os/os_vram_exclusive.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/frame_asm.h"

u32 OSi_TryLockVram(u16 banks, u16 lockId) {
    u32 irq;
    u32 locked;
    u32 pending;
    s32 bank;
    u32 clear;

    irq = OS_DisableInterrupts();
    locked = banks & data_02129c94;
    for (;;) {
        bank = 31 - Bits_CountLeadingZeros(locked);
        if (bank < 0) {
            break;
        }
        clear = ~(1 << bank);
        locked &= clear;
        if (data_02129c98[bank] != lockId) {
            OS_RestoreInterrupts(irq);
            return 0;
        }
    }
    pending = banks & 0x1ff;
    for (;;) {
        bank = 31 - Bits_CountLeadingZeros(pending);
        if (bank < 0) {
            break;
        }
        pending &= ~(1 << bank);
        data_02129c98[bank] = lockId;
        data_02129c94 |= 1 << bank;
    }
    OS_RestoreInterrupts(irq);
    return 1;
}

void OSi_UnlockVram(u16 banks, u16 lockId) {
    u32 locked;
    u32 irq;
    s32 bank;
    u32 clear;

    irq = OS_DisableInterrupts();
    locked = banks & data_02129c94 & 0x1ff;
    for (;;) {
        bank = 31 - Bits_CountLeadingZeros(locked);
        if (bank < 0) {
            break;
        }
        clear = ~(1 << bank);
        locked &= clear;
        if (data_02129c98[bank] == lockId) {
            data_02129c98[bank] = 0;
            data_02129c94 &= clear;
        }
    }
    OS_RestoreInterrupts(irq);
}
