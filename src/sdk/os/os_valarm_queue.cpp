#include "global.h"
#include "types.h"
#include "sdk/os/os_valarm.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_irq_state.h"
#include "sdk/gx/gx.h"

void OS_InitVAlarm(void) {
    if (data_02129c7c.initialised != 0) {
        return;
    }
    data_02129c7c.initialised = 1;
    data_02129c7c.head = NULL;
    data_02129c7c.tail = NULL;
    OS_DisableIrqMask(4);
    data_02129c7c.frame = 0;
    data_02129c7c.lastVCount = 0;
}

void OSi_InsertVAlarm(OsVAlarm *alarm) {
    OsVAlarm *next;
    OsVAlarm *prev;

    for (next = data_02129c7c.head; next != NULL; next = next->next) {
        if (next->frame >= alarm->frame && (next->frame != alarm->frame || next->vcount > alarm->vcount)) {
            prev = next->prev;
            alarm->prev = prev;
            alarm->next = next;
            next->prev = alarm;
            if (prev != NULL) {
                prev->next = alarm;
                return;
            }
            data_02129c7c.head = alarm;
            OSi_SetNextVAlarm(alarm);
            return;
        }
    }
    OSi_AppendVAlarm(alarm);
}

void OSi_AppendVAlarm(OsVAlarm *alarm) {
    OsVAlarm *tail;

    tail = data_02129c7c.tail;
    alarm->prev = tail;
    alarm->next = NULL;
    data_02129c7c.tail = alarm;
    if (tail != NULL) {
        tail->next = alarm;
        return;
    }
    data_02129c7c.head = alarm;
    OSi_SetNextVAlarm(alarm);
}

void OSi_DetachVAlarm(OsVAlarm *alarm) {
    OsVAlarm *prev;
    OsVAlarm *next;

    if (alarm == NULL) {
        return;
    }
    next = alarm->next;
    prev = alarm->prev;
    if (next != NULL) {
        next->prev = prev;
    } else {
        data_02129c7c.tail = prev;
    }
    if (prev != NULL) {
        prev->next = next;
    } else {
        data_02129c7c.head = next;
    }
}
