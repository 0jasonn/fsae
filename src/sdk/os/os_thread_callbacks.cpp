#include "sdk/os/os_thread.h"
#include "sdk/os/os_interrupts.h"

// Sleep alarm callback and the thread switch callback setter.
void OSi_SleepAlarmCallback(OsThread **argument) {
    OsThread *thread = *argument;
    *argument = 0;
    thread->sleepAlarm = 0;
    OS_WakeupThreadDirect(thread);
}

void *OS_SetSwitchThreadCallback(void *callback) {
    u32 irq = OS_DisableInterrupts();
    void *old = (void *)data_0212991c.threadSwitchCallback;
    data_0212991c.threadSwitchCallback = (void (*)(OsThread *, OsThread *))callback;
    OS_RestoreInterrupts(irq);
    return old;
}
