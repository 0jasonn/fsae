#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"
#include "engine/functions.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/card/card.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_thread.h"

#pragma optimization_level 2
void FATFSi_WaitForRequest(FatfsRequest *request) {
    s32 waiting;
    u32 irqState;
    FatfsRequest *volatile *link;

    waiting = 1;
    while (waiting != 0) {
        irqState = OS_DisableInterrupts();
        for (link = &data_021277e0.pending; *link != NULL; link = &(*link)->next) {
            if (*link == request) {
                waiting = 0;
                *link = (*link)->next;
                request->next = NULL;
                break;
            }
        }
        if (waiting != 0) {
            if (OS_GetProcMode() == 0x12) {
                PXIi_HandlerRecvFifoNotEmpty();
                WaitByLoop(10000);
            } else {
                Os_LinkThreadAndFlush(&data_021277e0.wakeQueue);
            }
        }
        OS_RestoreInterrupts(irqState);
    }
}
