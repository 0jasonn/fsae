#include "engine/functions.h"
#include "sdk/gx/gx_vramcnt.h"
#include "sdk/os/os_vram_exclusive.h"

// Clears the record, disables the VRAMCNT register of every bank in it and releases the VRAM lock of those banks.
// Returns the banks.
u32 disableBankForX_(u16 *bank) {
    u32 banks = *bank;
    *bank = 0;
    if (banks & 0x01) {
        *(volatile u8 *)0x4000240 = 0;
    }
    if (banks & 0x02) {
        *(volatile u8 *)0x4000241 = 0;
    }
    if (banks & 0x04) {
        *(volatile u8 *)0x4000242 = 0;
    }
    if (banks & 0x08) {
        *(volatile u8 *)0x4000243 = 0;
    }
    if (banks & 0x10) {
        *(volatile u8 *)0x4000244 = 0;
    }
    if (banks & 0x20) {
        *(volatile u8 *)0x4000245 = 0;
    }
    if (banks & 0x40) {
        *(volatile u8 *)0x4000246 = 0;
    }
    if (banks & 0x80) {
        *(volatile u8 *)0x4000248 = 0;
    }
    if (banks & 0x100) {
        *(volatile u8 *)0x4000249 = 0;
    }
    OSi_UnlockVram(banks, data_02129826);
    return banks;
}
