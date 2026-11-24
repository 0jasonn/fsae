#ifndef SDK_CARD_CARD_TASK_H
#define SDK_CARD_CARD_TASK_H

#include "sdk/card/card.h"

// Fields of the CARD work area used by command setup and task completion.
typedef struct CardTaskWork {
    void *commandArea;          // 0x000; first word is the command result
    u32 flags;                  // 0x004
    u8 unknown_008[0x4e0];
    void (*currentTask)(void *); // 0x4e8
    void (*completion)(void *);  // 0x4ec
    void *completionArg;        // 0x4f0
    u32 waitQueue[2];           // 0x4f4
    u8 unknown_4fc[0x20];
    void *waitingThread;        // 0x51c
} CardTaskWork;

extern u8 data_0217da80[];

extern "C" {
void CARDi_InitCommand(void);
void CARDi_EndTask(CardTaskWork *work);
void CARDi_OnFifoRecv(u32 fifo, u32 data, s32 error);
}

#endif
