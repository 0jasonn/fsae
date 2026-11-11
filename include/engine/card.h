#ifndef WIP_C_CARD_H
#define WIP_C_CARD_H

#include "types.h"

// NitroSDK CARD / OS functions and data used by the CARD unit.
extern "C" {
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
void OS_Terminate(void);
void Os_LinkThreadAndFlush(void *queue);
void OS_InitEvent(void *event);
void OS_CreateVAlarm(void *alarm);
u32 OS_WaitEventEx(void *event, u32 a, u32 b, u32 c);
s32 OS_GetBootType(void);
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
void MI_CpuCopy8(const void *src, void *dst, u32 size);
void Engine_Relay0201a070(void);
void PXI_SetFifoRecvCallback(u32 fifo, void (*callback)(u32, u32, s32));
void CARDi_NotifyEvent(u32 event, u32 arg);
void CARD_TerminateForPulledOut(void);

void CARDi_WaitAsyncThunk(void);
void CARDi_SetOwnSignature(const void *src);
void CARD_InitPulledOutCallback(void);
void CARDi_PulledOutCallback(u32 arg0, u32 arg1, s32 arg2);
s32 CARD_GetPulledOutFlag(void);
}

typedef struct CardLock {
    u8 pad_00[0x14];
    s32 owner;      // 0x14
    s32 count;      // 0x18
    u32 queue[2];   // 0x1c
    s32 level;      // 0x24
} CardLock;

// The stack block CARD_LockRom builds: an OSEvent at +0, an OSVAlarm at +0xc and the bus-lock listener at +0x34.
typedef struct CardLockEvent {
    u8 event[0x0c]; // OSEvent
    u8 alarm[0x1c]; // OSVAlarm
    u8 pad_28[0x34 - 0x28];
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
