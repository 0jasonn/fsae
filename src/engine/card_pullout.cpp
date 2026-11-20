#include "engine/functions.h"
#include "engine/card.h"

// NitroSDK card pull-out setup and PXI receive callback (0x020a46b0 through 0x020a4798).

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

// Handles PXI pull-out and insertion notices. State fields are defined by
// CardPulledOutState; message masks and event values come from this callback.
void CARDi_PulledOutCallback(u32 arg0, u32 message, s32 arg2) {
    u32 kind = message & 0x3f;

    if (kind == 0x11) {
        s32 shouldTerminate;
        s32 (*callback)(void);

        if (data_0217e2c0.pulledOut != 0) {
            return;
        }
        shouldTerminate = 1;
        data_0217e2c0.pulledOut = 1;
        CARDi_NotifyEvent(1, 0);
        callback = data_0217e2c0.callback;
        if (callback != NULL) {
            shouldTerminate = callback();
        }
        if (shouldTerminate != 0) {
            CARD_TerminateForPulledOut();
        }
        return;
    }
    if (kind == 2) {
        data_0217e2c0.insertCount++;
        data_0217e2c0.pulledOut = 0;
        CARDi_NotifyEvent(2, 0);
        return;
    }
    OS_Terminate();
}

// Returns the current card pull-out state.

s32 CARD_GetPulledOutFlag(void) {
    return data_0217e2c0.pulledOut;
}
