#include "engine/functions.h"
#include "sdk/os/os_irq.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_sleep_api.h"
#include "sdk/os/os_alarm.h"
#include "sdk/os/os_thread.h"


// Sleeps for count units (scaled by 0x82ea and divided by 64 into a 64-bit tick count): the current thread's alarm at
// +0xb0 is armed and the caller waits until the callback clears the thread pointer.

void Os_SleepAlarm(u32 count) {
    OsAlarm alarm;
    void *waiter;
    u64 ticks;
    u32 irq;

    OS_CreateAlarm(&alarm);
    waiter = *data_0212991c.curHolder;
    irq = OS_DisableInterrupts();
    ticks = ((u64)count * 0x82ea) >> 6;
    *(void **)((u8 *)waiter + 0xb0) = &alarm;
    func_0201918c(&alarm, ticks, OSi_SleepAlarmCallback, &waiter);
    if (waiter != NULL) {
        do {
            Os_LinkThreadAndFlush(NULL);
        } while (waiter != NULL);
    }
    OS_RestoreInterrupts(irq);
}
