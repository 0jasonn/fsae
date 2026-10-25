#ifndef WIP_A_OS_THREAD_H
#define WIP_A_OS_THREAD_H

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
} OsThreadRec;

// Scheduler block at data_0212991c: a pointer at +8 to a word that holds the current thread record.
typedef struct OsSchedBlock {
    u8 unk_00[8];
    OsThreadRec **curHolder;
    u8 unk_0c[8];
    u32 initStack;
} OsSchedBlock;

extern OsSchedBlock data_0212991c;

#endif
