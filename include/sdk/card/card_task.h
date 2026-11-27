#ifndef SDK_CARD_CARD_TASK_H
#define SDK_CARD_CARD_TASK_H

#include "sdk/card/card.h"

// The CARD task and resource-lock operations share the same work area.
typedef CardLock CardTaskWork;

typedef void (*CardRomReadFunction)(u32 mode, void *destination, u32 romAddress, u32 size);

typedef struct CardRomTransferCore {
    u32 romBase;
    CardRomReadFunction readFunction;
} CardRomTransferCore;

extern u8 data_0217da80[];
extern CardRomTransferCore data_0217e004;

extern "C" {
void CARDi_InitCommand(void);
void CARDi_EndTask(CardTaskWork *work);
void CARDi_OnFifoRecv(u32 fifo, u32 data, s32 error);
void *CARDi_GetDmaInterface(u32 mode);
void CARDi_RefreshRomCore(void);
void CARDi_DmaReadDone(void);
void CARDi_ReadRomSyncCore(CardTaskWork *work);
void CARDi_RefreshRom(u32 mask);
void CARDi_CheckPulledOutCore(u32 romId);
}

#endif
