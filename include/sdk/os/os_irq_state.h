#ifndef SDK_OS_OS_IRQ_STATE_H
#define SDK_OS_OS_IRQ_STATE_H

#include "types.h"

// Interrupt dispatch state of the TwlSDK OS library: the callback table (12 entries: DMA 0-3, NDMA 0-3, timers 0-3) and
// the per-source callback pointers live in main RAM / DTCM.
typedef struct IrqCallbackEntry {
    void (*callback)(void *);
    u32 enable;
    void *argument;
} IrqCallbackEntry;

typedef struct IrqThreadQueue {
    void *head;
    void *tail;
} IrqThreadQueue;

// Start of DTCM (0x02fe0000): the IRQ-check word that OS_WaitIrq polls is at +0x3ff8.
typedef struct DtcmWork {
    u8 unk_0000[0x3f7c];
    u32 irqStackChecker;
    u8 unk_3f80[0x3ff8 - 0x3f80];
    u32 irqCheckFlag;
} DtcmWork;

extern IrqCallbackEntry irqFunctionTable[12];
extern void (*irqCallbackInfo[32])(void);
extern IrqThreadQueue data_02fe00a0;
extern DtcmWork data_02fe0000;
extern u16 data_020dfb84[];

#define OS_IRQ_CHECK_FLAG (*(volatile u32 *)((u32)&data_02fe0000 + 0x3ff8))

#endif
