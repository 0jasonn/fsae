#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_thread.h"
#include "sdk/os/irqcount_api.h"
#include "sdk/os/os_irq_flush_api.h"
#include "sdk/os/os_thread_exit_api.h"

#include "sdk/os/os_mutex.h"

extern "C" void OSi_RemoveSpecifiedLinkFromQueue(OsThreadQueue *queue, OsThread *thread);
extern "C" void OSi_RemoveThreadFromList(OsThread *thread);

// Os_ExitCurrentThread() (0x02017a00): takes the current thread off its queues and mutexes, marks it as state 2, wakes the threads
// joined to it and terminates the thread for good.
void Os_ExitCurrentThread(void) {
    OsThread *thread;

    thread = *data_0212991c.curHolder;
    IrqCount_Acquire();
    OSi_UnlockAllMutex(thread);
    if (thread->link != NULL) {
        OSi_RemoveSpecifiedLinkFromQueue(thread->link, thread);
    }
    OSi_RemoveThreadFromList(thread);
    thread->state = 2;
    OS_WakeupThread(&thread->joinQueue);
    IrqCount_Release();
    Os_IrqDisabledFlush();
    OS_Terminate();
}
