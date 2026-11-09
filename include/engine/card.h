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

extern u8 data_0217da64[]; // the CARD work pointer chain
extern u8 data_0217dae0[]; // the CARD resource lock
extern u8 data_0217e2c0[]; // the card pull-out state
extern u8 data_0217e030[]; // the own card signature copy

#endif
