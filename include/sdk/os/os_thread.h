#ifndef SDK_OS_OS_THREAD_H
#define SDK_OS_OS_THREAD_H

// TwlSDK OS threads: thread records, wait queues, the scheduler block, context save/restore.
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
    u32 context[0x19];           // 0x00: saved CPU context (cpsr, r0-r12, sp, lr, pc, sp_svc ...)
    u32 state;                   // 0x64: 0 = waiting, 1 = ready, 2 = terminated
    struct OsThread *next;       // 0x68: next thread in the scheduler list
    u32 id;                      // 0x6c
    u32 priority;                // 0x70: lower runs first
    u32 unk_74;                  // 0x74: cleared by OS_CreateThread
    OsThreadQueue *link;         // 0x78: queue the thread sleeps on
    struct OsThread *linkPrev;   // 0x7c: neighbours in that queue
    struct OsThread *linkNext;   // 0x80
    struct OsMutex *blockedOn;   // 0x84: mutex the thread is waiting for
    OsMutexQueue mutexQueue;     // 0x88
    u32 stackBottom;             // 0x90: lowest stack address (holds the overflow marker)
    u32 stackTop;                // 0x94
    u32 stackWarning;            // 0x98
    OsThreadQueue joinQueue;     // 0x9c: threads waiting for this one to end
    u8 unk_a4[0xc];              // 0xa4
    struct OsAlarm *sleepAlarm;  // 0xb0: alarm armed by Os_SleepAlarm
    void (*exitHook)(u32 arg);   // 0xb4: called and cleared before the thread exits
    u8 unk_b8[8];                // 0xb8
} OsThread;

// Scheduler block at data_0212991c (0x2c bytes). +0x1c..+0x2b is the thread system state that dsd names data_02129938
// (OsThreadInfo below; its current-thread word is data_0212993c): code that loads that address on its own uses
// data_02129938, code that reaches it from the data_0212991c base uses the fields here. dsd also names +0x0c
// data_02129928.
typedef struct OsSchedBlock {
    /* 00 */ void (*switchCallback)(OsThread *from, OsThread *to);
    /* 04 */ u32 busy;                  // scheduler disable count (IrqCount_Acquire / IrqCount_Release)
    /* 08 */ OsThread **curHolder;      // points at the running-thread word (+0x20)
    /* 0c */ u32 initialized;           // set once by OS_InitThread
    /* 10 */ u8 unk_10[4];
    /* 14 */ u32 initStack;
    /* 18 */ volatile u32 nextThreadId; // incremented when OS_CreateThread allocates an ID
    /* 1c */ u16 needReschedule;        // = OsThreadInfo.needReschedule
    /* 1e */ u16 ready;                 // = OsThreadInfo.irqDepth: no switch while nonzero
    /* 20 */ OsThread *current;         // running thread
    /* 24 */ OsThread *list;            // all threads, sorted by priority
    /* 28 */ void (*threadSwitchCallback)(OsThread *from, OsThread *to);
} OsSchedBlock;

// Thread system state at data_02129938 (0x10 bytes, = data_0212991c + 0x1c; dsd names the current-thread word
// data_0212993c).
typedef struct OsThreadInfo {
    u16 needReschedule;                                       // 0x00: set when a switch was asked for while blocked
    u16 irqDepth;                                             // 0x02: no switch while nonzero
    OsThread *current;                                        // 0x04: running thread
    OsThread *list;                                           // 0x08: all threads by priority
    void (*switchCallback)(OsThread *from, OsThread *to);     // 0x0c
} OsThreadInfo;

extern OsSchedBlock data_0212991c;
extern OsThreadInfo data_02129938;
extern OsThread data_02129948;          // idle thread record
extern OsThread data_02129a08;          // main thread record
extern u8 data_02129b90[];              // idle thread stack

extern "C" {
void OS_InitThread(void);
void OS_CreateThread(OsThread *thread, void (*function)(void *), void *argument, void *stack, u32 stackSize,
                     u32 priority);
void OS_ExitThread(void);
void OS_WakeupThread(OsThreadQueue *queue);
void OS_WakeupThreadDirect(OsThread *thread);
OsThread *OS_SelectThread(void);
void OS_YieldThread(void);
BOOL OS_SetThreadPriority(OsThread *thread, u32 priority);
void OSi_SleepAlarmCallback(OsThread **argument);
void *OS_SetSwitchThreadCallback(void *callback);
u32 OSi_AllocateThreadId(void);

// Wait queues and the scheduler list.
void OSi_InsertLinkToQueue(OsThreadQueue *queue, OsThread *thread);
OsThread *OSi_RemoveLinkFromQueue(OsThreadQueue *queue);
OsThread *OSi_RemoveSpecifiedLinkFromQueue(OsThreadQueue *queue, OsThread *thread);
void OSi_InsertThreadToList(OsThread *thread);
void OSi_RemoveThreadFromList(OsThread *thread);

// Context: the saved context is the start of the thread record (hand-written ARM).
void OS_InitContext(OsThread *context, void (*function)(void), u32 stack);
u32 OS_SaveContext(OsThread *context);
void OS_LoadContext(OsThread *context);
void Os_StartContext(OsThread *context, u32 arg);
}

#endif
