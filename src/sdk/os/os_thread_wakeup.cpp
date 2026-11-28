#include "sdk/os/os_thread.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_switch_api.h"

// Wakes threads sleeping on a queue, or one thread directly, and picks the next thread to run.
void OS_WakeupThread(OsThreadQueue *queue) {
    u32 irq = OS_DisableInterrupts();
    if (queue->head != 0) {
        if (queue->head != 0) {
            do {
                OsThread *thread = OSi_RemoveLinkFromQueue(queue);
                thread->state = 1;
                thread->link = 0;
                thread->linkNext = 0;
                thread->linkPrev = 0;
            } while (queue->head != 0);
        }
        queue->tail = 0;
        queue->head = 0;
        Os_ThreadSwitch();
    }
    OS_RestoreInterrupts(irq);
}

void OS_WakeupThreadDirect(OsThread *thread) {
    u32 irq = OS_DisableInterrupts();
    thread->state = 1;
    Os_ThreadSwitch();
    OS_RestoreInterrupts(irq);
}

OsThread *OS_SelectThread(void) {
    OsThread *thread = data_0212991c.list;
    while (thread != 0 && thread->state != 1) {
        thread = thread->next;
    }
    return thread;
}
