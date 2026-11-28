#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_message.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/wm/wm_system.h"

// WmGetCommandBuffer4Arm7() (0x0201ec60): takes a free command block from the queue; NULL when none is free (a block
// the ARM7 still owns, bit 15 clear, is put back at the front).
void *WmGetCommandBuffer4Arm7(void) {
    void *block;

    if (!OS_ReceiveMessage(&data_0212b978, &block, 0)) {
        return NULL;
    }
    DC_InvalidateRange(block, 2);
    if (*(u16 *)block & 0x8000) {
        return block;
    }
    OS_JamMessage(&data_0212b978, block, 1);
    return NULL;
}

// WMi_SendCommand(command, wordCount, words...) (0x0201ecc0): fills a command block with the command id and wordCount
// argument words (taken from the caller's stack) and sends it to the ARM7. Returns 2 on success, 8 when no block is free
// or the FIFO refused it.
u32 WMi_SendCommand(u32 command, u16 wordCount, ...) {
    u8 *args;
    s32 i;
    WmCommandBuffer *buffer;
    s32 sent;
    u32 result;

    buffer = (WmCommandBuffer *)WmGetCommandBuffer4Arm7();
    if (buffer == NULL) {
        return 8;
    }
    buffer->command = command;
    args = (u8 *)((((u32)&wordCount) & ~3) + 4);
    for (i = 0; i < wordCount; i++) {
        buffer->argument[i] = *(u32 *)((args += 4) - 4);
    }
    DC_StoreRange(buffer, 0x100);
    sent = PXI_SendWordByFifo(10, (u32)buffer, 0);
    OS_SendMessage(&data_0212b978, buffer, 1);
    result = 8;
    if (sent >= 0) {
        result = 2;
    }
    return result;
}

// WMi_SendCommandDirect(data, size) (0x0201ed6c): like WMi_SendCommand, but copies a ready-made request of size bytes
// into the block.
u32 WMi_SendCommandDirect(u16 *data, u32 size) {
    void *buffer = WmGetCommandBuffer4Arm7();
    s32 sent;
    u32 result;

    if (buffer == NULL) {
        return 8;
    }
    MI_CpuCopy8(data, buffer, size);
    DC_StoreRange(buffer, size);
    sent = PXI_SendWordByFifo(10, (u32)buffer, 0);
    OS_SendMessage(&data_0212b978, buffer, 1);
    result = 8;
    if (sent >= 0) {
        result = 2;
    }
    return result;
}
