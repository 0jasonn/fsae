#include "engine/functions.h"
#include "engine/pair_block.h"
#include "global.h"
#include "types.h"

extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" u16 GetCRC16(u16 crc, const void *data, u32 size);
extern "C" s32 OS_IsValidDeliverArg(u32 arg);
extern "C" void OS_DisableMainExArena(void);
extern "C" s32 Pair_Restore(u32 arg);

// The pair buffer is re-read from the block at every use (the original keeps no local copy of the pointer).
#define PAIR_BUF ((u8 *)data_02129cac.pair)

// Pair_Restore(arg) (0x02019c0c): copies the saved 0x300-byte buffer from main RAM back into the pair buffer and
// checks its CRC. A matching CRC enables the pair (flags = 1) and clears bit 0 of the kind byte; otherwise the buffer
// is cleared and the main arena is disabled.
ARM s32 Pair_Restore(u32 arg) {
    u16 savedCrc;

    if (OS_IsValidDeliverArg(arg) == 0) {
        return -1;
    }
    if (PAIR_BUF == NULL) {
        return -1;
    }
    MI_CpuCopy8((const void *)0x2000000, PAIR_BUF, 0x300);
    savedCrc = *(u16 *)(PAIR_BUF + 0x10);
    *(u16 *)(PAIR_BUF + 0x10) = 0;
    *(u16 *)(PAIR_BUF + 0x10) = GetCRC16(0xffff, PAIR_BUF, 0x300);
    if (savedCrc != *(u16 *)(PAIR_BUF + 0x10)) {
        MI_CpuFill8(PAIR_BUF, 0, 0x300);
        OS_DisableMainExArena();
        return 0;
    }
    PAIR_BUF[9] &= 0xfe;
    data_02129cac.flags = 1;
    return 0;
}
