#include "global.h"
#include "types.h"
#include "sdk/os/os_alarm.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_tick.h"
#include "sdk/os/os_irq_state.h"

// Timer interrupt body: pops the expired alarm, runs its handler and re-queues it if periodic.
void OSi_ArrangeTimer(void) {
    OsAlarm *alarm;
    OsAlarm *next;
    void (*handler)(void *);
    u64 now;

    *(volatile u16 *)0x04000106 = 0;
    OS_DisableIrqMask(0x10);
    OS_IRQ_CHECK_FLAG |= 0x10;
    now = OS_GetTick();
    alarm = data_02129c70.head;
    if (alarm == NULL) {
        return;
    }
    if (now < alarm->fire) {
        OSi_SetTimer(alarm);
        return;
    }
    next = alarm->next;
    data_02129c70.head = next;
    if (next == NULL) {
        data_02129c70.tail = NULL;
    } else {
        next->prev = NULL;
    }
    handler = alarm->handler;
    if (alarm->period == 0) {
        alarm->handler = NULL;
    }
    if (handler != NULL) {
        handler(alarm->argument);
    }
    if (alarm->period != 0) {
        alarm->handler = handler;
        OSi_InsertAlarm(alarm, 0);
    }
    if (data_02129c70.head != NULL) {
        OSi_SetTimer(data_02129c70.head);
    }
}
