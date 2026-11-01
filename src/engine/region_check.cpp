#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/a_extern.h"

// Range check for a memory region (addr, len, dir): dir 0 means the region grows up from addr, dir 0x800000 means
// it grows down. The region is rejected (OS_Terminate) when either end lies in the 0x04000000 (I/O) or 0x08000000
// (cartridge) top-byte area. Returns when the flag word at 0x04004008 (bit 0) and flags are clear and both ends
// are in range.
// 0x020159cc
ARM void Region_CheckNotIoOrRom(u32 flags, u32 addr, u32 len, u32 dir) {
    u32 ioBusy;
    u32 startKind;
    u32 endKind;
    ioBusy = (*(volatile u32 *)0x4004008) & 1;
    ioBusy = ioBusy != 0;
    if (ioBusy != 0 || flags != 0) {
        return;
    }
    startKind = addr & 0xff000000;
    if (dir != 0) {
        if (dir == 0x800000) {
            addr -= len;
        }
    } else {
        addr += len;
    }
    endKind = addr & 0xff000000;
    if (startKind != 0x4000000 && startKind < 0x8000000) {
        if (endKind != 0x4000000 && endKind < 0x8000000) {
            return;
        }
    }
    OS_Terminate();
}
