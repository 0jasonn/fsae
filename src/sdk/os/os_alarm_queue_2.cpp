#include "global.h"
#include "types.h"
#include "sdk/os/os_alarm.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_tick.h"

void OSi_InsertAlarm(void *alarmArg, u64 fire) {
    OsAlarm *alarm = (OsAlarm *)alarmArg;
    OsAlarm *next;
    OsAlarm *prev;
    u64 now;
    u64 count;

    if (alarm->period != 0) {
        now = OS_GetTick();
        fire = alarm->start;
        if (fire < now) {
            count = (now - fire) / alarm->period + 1;
            fire += alarm->period * count;
        }
    }
    alarm->fire = fire;
    for (next = data_02129c70.head; next != NULL; next = next->next) {
        if ((s64)(fire - next->fire) < 0) {
            alarm->prev = next->prev;
            next->prev = alarm;
            alarm->next = next;
            prev = alarm->prev;
            if (prev != NULL) {
                prev->next = alarm;
                return;
            }
            data_02129c70.head = alarm;
            OSi_SetTimer(alarm);
            return;
        }
    }
    alarm->next = NULL;
    prev = data_02129c70.tail;
    data_02129c70.tail = alarm;
    alarm->prev = prev;
    if (prev != NULL) {
        prev->next = alarm;
        return;
    }
    data_02129c70.tail = alarm;
    data_02129c70.head = alarm;
    OSi_SetTimer(alarm);
}
