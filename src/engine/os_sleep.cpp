#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Current-thread record: the thread pointer sits at +8 of data_0212991c and points at the record whose +0xb0 holds the
// sleep alarm.
typedef struct OsSleepOwner {
    u8 unk_00[8];
    void **thread;           // 0x08: pointer to the record pointer
} OsSleepOwner;

extern OsSleepOwner data_0212991c;

extern "C" void OS_CreateAlarm(void *alarm);
extern "C" u32 OS_DisableInterrupts(void);
extern "C" void OS_RestoreInterrupts(u32 state);
extern "C" void OSi_SleepAlarmCallback(void);
extern "C" void func_0201918c(void *alarm, u32 lo, u32 hi, void *callback, void *arg);
extern "C" void Os_LinkThreadAndFlush(s32 flag);

// Sleeps for count units (scaled by 0x82ea and divided by 64 into a 64-bit tick count): the current thread's alarm at
// +0xb0 is armed and the caller waits until the callback clears the thread pointer.
extern "C" void Os_SleepAlarm(u32 count);

ARM void Os_SleepAlarm(u32 count) {
    u8 alarm[0x2c];
    void *waiter;
    u64 ticks;
    u32 irq;

    OS_CreateAlarm(alarm);
    waiter = data_0212991c.thread[0];
    irq = OS_DisableInterrupts();
    ticks = ((u64)count * 0x82ea) >> 6;
    *(void **)((u8 *)waiter + 0xb0) = alarm;
    func_0201918c(alarm, (u32)ticks, (u32)(ticks >> 32), OSi_SleepAlarmCallback, &waiter);
    if (waiter != NULL) {
        do {
            Os_LinkThreadAndFlush(0);
        } while (waiter != NULL);
    }
    OS_RestoreInterrupts(irq);
}
