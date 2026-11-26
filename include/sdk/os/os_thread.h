#ifndef SDK_OS_OS_THREAD_H
#define SDK_OS_OS_THREAD_H

#include "global.h"
#include "types.h"

struct OsThread;
struct OsMutex;
struct OsAlarm;

typedef struct OsThreadQueue {
    struct OsThread *head;
    struct OsThread *tail;
} OsThreadQueue;

// Mutexes a thread owns, linked through OsMutex.next / prev.
typedef struct OsMutexQueue {
    struct OsMutex *head;
    struct OsMutex *tail;
} OsMutexQueue;

// Thread record (0xc0 bytes): the saved context first, then the scheduler and wait bookkeeping.
typedef struct OsThread {
    u8 unk_00[0x64];             // 0x00: saved CPU context
    u32 state;                   // 0x64: 0 = waiting, 1 = ready, 2 = terminated
    struct OsThread *next;       // 0x68: next thread in the scheduler list
    u32 id;                      // 0x6c
    u8 unk_70[8];                // 0x70
    OsThreadQueue *link;         // 0x78: queue the thread sleeps on
    struct OsThread *linkPrev;   // 0x7c: neighbours in that queue
    struct OsThread *linkNext;   // 0x80
    struct OsMutex *blockedOn;   // 0x84: mutex the thread is waiting for
    OsMutexQueue mutexQueue;     // 0x88
    u8 unk_90[0xc];              // 0x90: stack bounds
    OsThreadQueue joinQueue;     // 0x9c: threads waiting for this one to end
    u8 unk_a4[0xc];              // 0xa4
    struct OsAlarm *sleepAlarm;  // 0xb0: alarm armed by Os_SleepAlarm
    void (*exitHook)(u32 arg);   // 0xb4: called and cleared before the thread exits
    u8 unk_b8[8];                // 0xb8
} OsThread;

// Scheduler block at data_0212991c: a pointer at +8 to a word that holds the current thread record.
typedef struct OsSchedBlock {
    u8 unk_00[8];
    OsThread **curHolder;
    u8 unk_0c[8];
    u32 initStack;
    volatile u32 nextThreadId; // 0x18: incremented when OS_CreateThread allocates an ID
} OsSchedBlock;

// Thread system state at data_02129938 (0x10 bytes; dsd names the current-thread word data_0212993c).
typedef struct OsThreadInfo {
    u16 needReschedule;                                       // 0x00: set when a switch was asked for while blocked
    u16 unk_02;                                               // 0x02
    OsThread *current;                                        // 0x04: running thread
    OsThread *list;                                           // 0x08: all threads by priority
    void (*switchCallback)(OsThread *from, OsThread *to);     // 0x0c
} OsThreadInfo;

extern OsSchedBlock data_0212991c;
extern OsThreadInfo data_02129938;

extern "C" {
// Not decompiled yet.
void OS_WakeupThread(OsThreadQueue *queue);
}

#endif
