#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_thread.h"

void FATFS_RegisterResultBuffer(FatfsWaiter *waiter, s32 enable) {
    u32 irqState;
    FatfsWaiter *previous;
    FatfsWaiter *current;

    irqState = OS_DisableInterrupts();
    if (enable != 0) {
        waiter->next = data_021277e0.waiters;
        waiter->thread = (u32)data_02129938.current;
        waiter->request = NULL;
        waiter->result = 0;
        data_021277e0.waiters = waiter;
    } else {
        previous = (FatfsWaiter *)&data_021277e0.waiters;
        for (current = data_021277e0.waiters; current != NULL; current = current->next) {
            if (current == waiter) {
                previous->next = current->next;
                break;
            }
            previous = current;
        }
    }
    OS_RestoreInterrupts(irqState);
}
