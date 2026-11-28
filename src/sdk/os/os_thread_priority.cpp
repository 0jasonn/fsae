#include "sdk/os/os_thread.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_switch_api.h"

// Changes the priority of a thread and reinserts it into the scheduler list.
BOOL OS_SetThreadPriority(OsThread *thread, u32 priority) {
    OsThread *cur;
    OsThread *prev;
    u32 irq;

    cur = data_0212991c.list;
    prev = 0;
    irq = OS_DisableInterrupts();
    while (cur != 0 && cur != thread) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == 0 || cur == &data_02129948) {
        OS_RestoreInterrupts(irq);
        return 0;
    }
    if (cur->priority != priority) {
        if (prev == 0) {
            data_0212991c.list = thread->next;
        } else {
            prev->next = thread->next;
        }
        thread->priority = priority;
        OSi_InsertThreadToList(thread);
        Os_ThreadSwitch();
    }
    OS_RestoreInterrupts(irq);
    return 1;
}
