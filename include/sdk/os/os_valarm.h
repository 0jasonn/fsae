#ifndef SDK_OS_OS_VALARM_H
#define SDK_OS_OS_VALARM_H

// TwlSDK OS V-count alarms (0x28 bytes each).
#include "types.h"

typedef struct OsVAlarm {
    void (*handler)(void *);  // 0x00: cleared while the handler runs
    void *argument;           // 0x04
    u32 tag;                  // 0x08
    u32 frame;                // 0x0c: frame number in which the alarm fires
    s16 vcount;               // 0x10: V-count line at which it fires
    s16 delay;                // 0x12: lines the handler may be late by before the alarm is skipped
    struct OsVAlarm *prev;    // 0x14
    struct OsVAlarm *next;    // 0x18
    s32 period;               // 0x1c: nonzero for periodic alarms
    u32 finished;             // 0x20: cleared by OS_CreateVAlarm
    s32 canceled;             // 0x24
} OsVAlarm;

// data_02129c7c: V-count alarm queue, sorted by (frame, vcount).
typedef struct OsVAlarmQueue {
    u16 initialised;          // 0x00
    u8 unk_02[2];             // 0x02
    s32 lastVCount;           // 0x04: V-count seen by the last OSi_GetVFrame
    u32 frame;                // 0x08: running frame counter
    OsVAlarm *head;           // 0x0c
    OsVAlarm *tail;           // 0x10
} OsVAlarmQueue;

extern OsVAlarmQueue data_02129c7c;

extern "C" {
void OS_CreateVAlarm(OsVAlarm *alarm);
void OS_InitVAlarm(void);
void OSi_InsertVAlarm(OsVAlarm *alarm);
void OSi_AppendVAlarm(OsVAlarm *alarm);
void OSi_DetachVAlarm(OsVAlarm *alarm);
void func_02019434(OsVAlarm *alarm, s16 vcount, s16 delay, void (*handler)(void *), void *argument); // OS_SetVAlarm
void OSi_SetNextVAlarm(OsVAlarm *alarm);
void OSi_VAlarmHandler(void);
s32 OSi_CompareVCount(OsVAlarm *alarm, s32 frame, s32 vcount);
s32 OSi_GetVFrame(s32 vcount);
}

#endif
