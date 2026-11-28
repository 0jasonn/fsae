#include "global.h"
#include "types.h"
#include "sdk/os/os_alarm.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_tick.h"

void OSi_SetTimer(OsAlarm *alarm) {
    s64 remaining;
    u16 reload;

    u64 now = OS_GetTick();
    reload = 0;
    *(volatile u16 *)0x04000106 = 0;
    remaining = (s64)(alarm->fire - now);
    OSi_EnterTimerCallback(1, (void (*)(void *))OSi_AlarmHandler, NULL);
    if (remaining < 0) {
        reload = 0xfffe;
    } else if (remaining < 0x10000) {
        reload = (u16)~(u32)remaining;
    }
    *(volatile u16 *)0x04000104 = reload;
    *(volatile u16 *)0x04000106 = 0xc1;
    OS_EnableIrqMask(0x10);
}

