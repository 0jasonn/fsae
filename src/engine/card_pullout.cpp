#include "engine/functions.h"
#include "engine/card.h"

// NitroSDK card pull-out unit. Functions in this file:
//   CARDi_WaitAsyncThunk (0x020a46b0), CARDi_SetOwnSignature (0x020a46bc),
//   CARD_InitPulledOutCallback (0x020a46d4), CARD_GetPulledOutFlag (0x020a4798).
// The PXI receive callback CARDi_PulledOutCallback (0x020a4708) is parked in scratch/agentC/nonmatching
// (its two instructions that load the state pointer use r2/r3 the other way round).

void CARDi_WaitAsyncThunk(void) {
    CARDi_WaitAsync();
}

void CARDi_SetOwnSignature(const void *src) {
    MI_CpuCopy8(src, data_0217e030, 0x88);
}

void CARD_InitPulledOutCallback(void) {
    Engine_Relay0201a070();
    data_0217e2c0.insertCount = 0;
    data_0217e2c0.pulledOut = 0;
    PXI_SetFifoRecvCallback(0xe, CARDi_PulledOutCallback);
    data_0217e2c0.callback = NULL;
}

