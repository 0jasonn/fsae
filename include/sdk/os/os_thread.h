#ifndef SDK_OS_OS_THREAD_H
#define SDK_OS_OS_THREAD_H

#include "global.h"
#include "types.h"

// Thread record: its link word at +0x78, a state word at +0x64 and the wait object at +0x9c.
typedef struct OsThreadRec {
    u8 unk_00[0x64];
    u32 state;
    u8 unk_68[0x10];
    void *link;
    u8 unk_7c[0x20];
    u8 waitObject[1];
    u8 unk_9d[0xb4 - 0x9d];
    void (*exitHook)(u32 arg); // 0xb4: called and cleared before the thread exits
} OsThreadRec;

// Scheduler block at data_0212991c: a pointer at +8 to a word that holds the current thread record.
typedef struct OsSchedBlock {
    u8 unk_00[8];
    OsThreadRec **curHolder;
    u8 unk_0c[8];
    u32 initStack;
    volatile u32 nextThreadId; // 0x18: incremented when OS_CreateThread allocates an ID
} OsSchedBlock;

extern OsSchedBlock data_0212991c;

#endif
