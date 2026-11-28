#ifndef SDK_OS_OS_ALARM_H
#define SDK_OS_OS_ALARM_H

// TwlSDK OS tick alarms (0x2c bytes each).
#include "types.h"

typedef struct OsAlarm {
    void (*handler)(void *); // 0x00: cleared once the alarm has fired and is not periodic
    void *argument;          // 0x04
    u32 tag;                 // 0x08
    u64 fire;                // 0x0c: tick at which the alarm fires
    struct OsAlarm *prev;    // 0x14
    struct OsAlarm *next;    // 0x18
    u64 period;              // 0x1c: 0 for one-shot alarms
    u64 start;               // 0x24: tick of the first period
} OsAlarm;

// data_02129c70: queue of armed alarms, sorted by fire time.
typedef struct OsAlarmQueue {
    u16 initialised;         // 0x00
    u8 unk_02[2];            // 0x02
    OsAlarm *head;           // 0x04: next alarm to fire
    OsAlarm *tail;           // 0x08
} OsAlarmQueue;

extern OsAlarmQueue data_02129c70;

extern "C" {
void OS_CreateAlarm(OsAlarm *alarm);
void OSi_AlarmHandler(void);  // timer interrupt handler (hand-written ARM)
void OSi_SetTimer(OsAlarm *alarm);
void OSi_InsertAlarm(void *alarm, u64 fire); // an OsAlarm; src/sdk/os/os_alarm_set.cpp declares it with void *
void OSi_ArrangeTimer(void);
void func_0201918c(OsAlarm *alarm, u64 delay, void *callback, void *arg); // OS_SetAlarm (src/sdk/os/os_alarm_set.cpp)
}

#endif
