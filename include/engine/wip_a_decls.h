#ifndef WIP_A_DECLS_H
#define WIP_A_DECLS_H

// Prototypes and data used by the round 13 implementer A files (src/wip/A). The reviewer moves the functions
// into engine/functions.h and the data into the shared data headers.
#include "types.h"
#include "engine/callees.h"

// Task state record at data_02127280 (bss), shared with src/engine/task_state.cpp.
typedef struct TaskDispatchState {
    void (*pending)(void);   // 0x00: run and cleared by Task_Dispatch
    void (*callback)(void);  // 0x04: run once by Task_Flush while the task is not active
    s32 queued;              // 0x08: entries waiting in Task_QueueTable
    u32 active;              // 0x0c
} TaskDispatchState;

// Thread record at the main thread pointer (data_02129938[1]); only the tag used by the task lock is named.
typedef struct TaskLockThread {
    u8 unk_00[0x6c];
    u32 lockTag;             // 0x6c: identifies the owner of the task lock
} TaskLockThread;

extern "C" {
s32 OS_TryLockMutex(void *mutex);
void Entry_Update(void *arg);
}

// C++ linkage (mangled _Z16Forward_0200b10cv), defined in src/engine/stub_4.cpp.
void Forward_0200b10c(void);

// Timer record used by Timer_Advance (src/wip/A/timer_advance.cpp). Offsets match TimerSnapshot in src/engine/timer.cpp.
typedef struct TimerAdvanceRec {
    u32 owner;                                    // 0x00: first argument of the callback
    u32 flags;                                    // 0x04: bit 12 skips the delta stub
    u8 unk_08[0x10];
    u32 value;                                    // 0x18: live counter, advanced by delta
    u32 lastValue;                                // 0x1c
    u32 limit;                                    // 0x20
    u32 snapshot;                                 // 0x24
    s32 delta;                                    // 0x28
    u8 unk_2c[0x14];
    s32 (*callback)(u32, u32, s32 *, u32);        // 0x40
    u8 unk_44[4];
    u32 callbackArg;                              // 0x48
} TimerAdvanceRec;

extern "C" {
// Empty stub at 0x020056e8: its symbol is the C++ name _Z13Stub_020056e8v (src/engine/stub_2.cpp); called with two
// register arguments here.
void _Z13Stub_020056e8v(u32 value, s32 *ptr);
void Timer_Snapshot(void *rec);
}

// Entry record (0x4c bytes) walked by Entries_ProcessAll and processed by Entry_Update. Its timer fields match
// TimerAdvanceRec.
typedef struct EntryFlagWord {
    u32 unk_b0 : 2;
    u32 kind : 3;            // bits 2..4: kind 1 means done
    u32 unk_b5 : 2;
    u32 mode : 3;            // bits 7..9: must be nonzero
    u32 unk_b10 : 22;
} EntryFlagWord;

typedef struct EntryStateWord {
    u32 state : 3;           // low three bits: the entry state
    u32 unk_b3 : 29;
} EntryStateWord;

typedef struct EntryRec {
    u8 unk_00[4];
    EntryFlagWord flags;     // 0x04
    EntryStateWord stateWord; // 0x08
    u8 unk_0c;
    u8 finished;             // 0x0d: set when the timer step reports an error
    u8 unk_0e[0x0a];
    u32 value;               // 0x18
    u8 unk_1c[0x0c];
    s32 delta;               // 0x28
    u8 unk_2c[0x20];
} EntryRec;

// PMi send state at data_0212b920: busy flag at +0x30 and three parameters saved for the send.
typedef struct PmiSendState {
    u8 unk_00[0x30];
    s32 busy;                // 0x30
    u32 param34;             // 0x34
    u32 param38;             // 0x38
    u32 param3c;             // 0x3c
} PmiSendState;

extern "C" {
s32 Entries_ProcessAll(void);
void PMi_SendPxiData(u32 word);
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
s32 Timer_Advance(TimerAdvanceRec *rec, s32 *deltaOut);
}

extern TaskDispatchState data_02127280;
extern void (*Task_QueueTable[])(void);
extern u8 Task_LockMutex[];
extern u32 Task_LockOwnerTag;
extern s32 Task_LockDepth;
extern u32 data_02129938[];
extern u8 data_02129864[];
extern PmiSendState data_0212b920;

#endif
