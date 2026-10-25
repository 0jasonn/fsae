#include "engine/functions.h"
#include "engine/callees.h"
#include "global.h"
#include "types.h"
#include "engine/os_thread.h"

extern "C" u32 IrqCount_Acquire(void);
extern "C" u32 IrqCount_Release(void);
extern "C" void OSi_UnlockAllMutex(OsThreadRec *thread);
extern "C" void OSi_RemoveSpecifiedLinkFromQueue(void *link, OsThreadRec *thread);
extern "C" void OSi_RemoveThreadFromList(OsThreadRec *thread);
extern "C" void OS_WakeupThread(void *waitObject);
extern "C" void Os_IrqDisabledFlush(void);
extern "C" void OS_Terminate(void);
extern "C" void Os_ExitCurrentThread(void);

// Os_ExitCurrentThread() (0x02017a00): takes the current thread off its queues and mutexes, marks it as state 2, wakes its
// wait object and terminates the thread for good.
ARM void Os_ExitCurrentThread(void) {
    OsThreadRec *thread;

    thread = *data_0212991c.curHolder;
    IrqCount_Acquire();
    OSi_UnlockAllMutex(thread);
    if (thread->link != NULL) {
        OSi_RemoveSpecifiedLinkFromQueue(thread->link, thread);
    }
    OSi_RemoveThreadFromList(thread);
    thread->state = 2;
    OS_WakeupThread(thread->waitObject);
    IrqCount_Release();
    Os_IrqDisabledFlush();
    OS_Terminate();
}
