#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"
#include "engine/functions.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/card/card.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/fatfs/stdconv_table_wrap_api.h"

u32 FATFSi_GetThreadHandle(void) {
    if (OS_GetProcMode() == 0x12) {
        return FATFS_THREAD_HANDLE_IRQ;
    }
    return (u32)data_02129938.current;
}

void FATFSi_SetRequestBuffer(FatfsRequest *request, void (*callback)(FatfsRequest *), u32 argument) {
    u32 irqState;

    irqState = OS_DisableInterrupts();
    request->threadHandle = FATFSi_GetThreadHandle();
    request->callback = callback;
    request->callbackArgument = argument;
    request->nextRegistered = data_021277e0.registered;
    data_021277e0.registered = request;
    OS_RestoreInterrupts(irqState);
}
