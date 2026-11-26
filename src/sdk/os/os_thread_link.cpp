#include "engine/functions.h"
#include "sdk/os/os_irq.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_thread.h"
#include "sdk/os/os_switch_api.h"

extern "C" void OSi_InsertLinkToQueue(OsThreadQueue *queue, OsThread *thread);

// Os_LinkThreadAndFlush(queue) (0x02017a5c): with interrupts off, puts the current thread on queue (when queue is not
// NULL) and clears the state word of the current thread, then runs Os_ThreadSwitch and restores the interrupts.
void Os_LinkThreadAndFlush(void *queue) {
    OsThreadQueue *threadQueue = (OsThreadQueue *)queue;
    u32 state;
    OsThread *current;

    state = OS_DisableInterrupts();
    current = *data_0212991c.curHolder;
    if (threadQueue != NULL) {
        current->link = threadQueue;
        OSi_InsertLinkToQueue(threadQueue, current);
    }
    current->state = 0;
    Os_ThreadSwitch();
    OS_RestoreInterrupts(state);
}
