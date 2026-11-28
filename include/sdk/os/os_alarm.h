#ifndef SDK_OS_OS_ALARM_H
#define SDK_OS_OS_ALARM_H

// TwlSDK OS tick alarms (0x2c bytes each).
#include "types.h"

typedef struct OsAlarm {
    void (*handler)(void *); // 0x00
    void *argument;          // 0x04
    u32 tag;                 // 0x08
    u8 unk_0c[0x20];         // 0x0c: fire time, list links, period and start
} OsAlarm;

extern "C" {
void OS_CreateAlarm(OsAlarm *alarm);
void OSi_AlarmHandler(void);  // timer interrupt handler (hand-written ARM)
void OSi_ArrangeTimer(void);  // not decompiled yet
void func_0201918c(OsAlarm *alarm, u64 delay, void *callback, void *arg); // OS_SetAlarm (src/sdk/os/os_alarm_set.cpp)
}

#endif
