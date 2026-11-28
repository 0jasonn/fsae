#include "sdk/os/os_thread.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/irqcount_api.h"
#include "sdk/mi/mi_memory.h"

// Thread creation and exit.
void OS_CreateThread(OsThread *thread, void (*function)(void *), void *argument, void *stack, u32 stackSize,
                     u32 priority) {
    u32 irq;
    u32 stackBottom;

    irq = OS_DisableInterrupts();
    thread->id = OSi_AllocateThreadId();
    thread->priority = priority;
    thread->state = 0;
    thread->unk_74 = 0;
    OSi_InsertThreadToList(thread);
    thread->stackTop = (u32)stack;
    thread->stackWarning = 0;
    stackBottom = (u32)stack - stackSize;
    thread->stackBottom = stackBottom;
    *((u32 *)stack - 2) = 0xfddb597d;
    *(u32 *)thread->stackBottom = 0x7bf9dd5b;
    thread->joinQueue.tail = 0;
    thread->joinQueue.head = 0;
    OS_InitContext(thread, (void (*)(void))function, (u32)stack - 8);
    thread->context[1] = (u32)argument;
    thread->context[15] = (u32)OS_ExitThread;
    OSi_CpuClear32(0, (u8 *)stackBottom + 4, stackSize - 0xc);
    thread->blockedOn = 0;
    thread->mutexQueue.head = 0;
    thread->mutexQueue.tail = 0;
    Obj_SetWordB4(thread, 0);
    thread->link = 0;
    thread->linkNext = 0;
    thread->linkPrev = 0;
    OSi_CpuClear32(0, thread->unk_a4, 0xc);
    thread->sleepAlarm = 0;
    OS_RestoreInterrupts(irq);
}

void OS_ExitThread(void) {
    OS_DisableInterrupts();
    Os_StartContext(data_0212991c.current, 0);
}
