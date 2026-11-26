#ifndef SDK_OS_OS_VALARM_H
#define SDK_OS_OS_VALARM_H

// TwlSDK OS V-count alarms (0x28 bytes each).
#include "types.h"

typedef struct OsVAlarm {
    void (*handler)(void *); // 0x00
    void *argument;          // 0x04
    u32 tag;                 // 0x08
    u8 unk_0c[0x14];         // 0x0c: frame, fire line, delay, list links and the periodic flag
    u32 finished;            // 0x20: cleared by OS_CreateVAlarm
    u8 unk_24[4];            // 0x24
} OsVAlarm;

extern "C" {
void OS_CreateVAlarm(OsVAlarm *alarm);
}

#endif
