#ifndef SDK_CARD_CARD_H
#define SDK_CARD_CARD_H

#include "types.h"
#include "sdk/pxi/pxi_fifo.h"  // Engine_Relay0201a070, PXI_SetFifoRecvCallback
#include "sdk/os/os_boot.h"
#include "sdk/os/os_event.h"
#include "sdk/os/os_thread.h"
#include "sdk/os/os_valarm.h"

// NitroSDK CARD / OS functions and data used by the CARD unit.
extern "C" {
void Os_LinkThreadAndFlush(void *queue);
void CARDi_PeekEventListener(void *event);
s32 CARDi_LockBusCondition(u16 *value);
s32 CardBus_Release(u32 owner);

void *CARDi_GetWorkPtr(void);
void CARDi_GetWork(void);
void CARDi_SetWorkPtr(void *work);
void *CARD_GetRomHeader(void);
void *CARD_GetOwnRomHeader(void);
void *CARD_GetOwnRomHeaderTWL(void);
void CARDi_AcquireLock(u32 owner, u32 level);
void CARDi_ReleaseLock(u32 owner, u32 level);
s32 CARDi_GetAccessLevel(void);

// Pulled-out callback unit.
void CARDi_WaitAsync(void);
s32 CARDi_WaitForTask(void *work, u32 flag, void (*callback)(void *), void *arg);
s32 CARDi_IsNormalMode(void);
void CARDi_SetRomOp(u32 command, u32 address);
void CARDi_StartRomPageTransfer(u32 page);
u32 CARDi_ReadRomIDCore(void);
void CARDi_NotifyEvent(u32 event, u32 arg);
void CARD_TerminateForPulledOut(void);

void CARDi_WaitAsyncThunk(void);
void CARDi_SetOwnSignature(const void *src);
void CARD_InitPulledOutCallback(void);
void CARDi_PulledOutCallback(u32 arg0, u32 arg1, s32 arg2);
s32 CARD_GetPulledOutFlag(void);
}

typedef struct CardLock {
    void *commandArea; // 0x00; first word is the command result
    u32 flags;        // 0x04
    u8 pad_08[0x0c];
    s32 owner;      // 0x14
    s32 count;      // 0x18
    OsThreadQueue queue; // 0x1c
    s32 level;      // 0x24
    u8 unknown_028[0x4c0];
    void (*currentTask)(void *); // 0x4e8
    void (*completion)(void *);  // 0x4ec
    void *completionArg;        // 0x4f0
    OsThreadQueue waitQueue;    // 0x4f4: threads waiting for the task
    u32 romAddress;             // 0x4fc
    void *destination;          // 0x500
    u32 transferSize;           // 0x504
    u8 unknown_508[0x14];
    void *waitingThread;        // 0x51c
} CardLock;

// The stack block CARD_LockRom builds: an OSEvent at +0, an OSVAlarm at +0xc and the bus-lock listener at +0x34.
typedef struct CardLockEvent {
    OsEvent event;  // 0x00
    OsVAlarm alarm; // 0x0c
    void *fn;       // 0x34
    void *arg;      // 0x38
    u8 pad_3c[4];
} CardLockEvent;

// The game-card header field at 0x1b4, as bitfields.
typedef struct CardRomHeader {
    u8 pad[0x1b4];
    u32 rsv5:5;
    u32 f5:1;
    u32 rsv6:2;
    u32 f8:1;
    u32 rsv7:6;
    u32 f15:1;
    u32 f16:1;
} CardRomHeader;

typedef struct CardPulledOutState {
    s32 insertCount;        // 0x00: number of card insertions
    s32 pulledOut;          // 0x04: set while the card is pulled out
    s32 (*callback)(void);  // 0x08: user callback run when the card is pulled out
} CardPulledOutState;

extern u8 data_0217da64[]; // the CARD work pointer chain
extern CardLock data_0217dae0; // the CARD resource lock
extern CardPulledOutState data_0217e2c0; // the card pull-out state
extern u8 data_0217e030[]; // the own card signature copy

#endif
