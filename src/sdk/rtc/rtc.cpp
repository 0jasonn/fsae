#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/rtc/rtc.h"

// RTC_Init() (0x0201a354): one-time setup, then waits until the ARM7 side has its RTC callback ready and installs ours.
void RTC_Init(void) {
    if (data_02129d50.initialized != 0) {
        return;
    }
    data_02129d50.initialized = 1;
    data_02129d50.busy = 0;
    data_02129d50.callback = NULL;
    data_02129d50.unk_20 = 0;
    data_02129d50.timeBuffer = NULL;
    data_02129d50.unk_10 = 0;
    Engine_Relay0201a070();
    while (!PXI_IsCallbackReady(5, 1)) {
    }
    PXI_SetFifoRecvCallback(5, RtcCommonCallback);
}

// RTC_GetTimeAsync(time, callback, callbackArg) (0x0201a3c0): returns 0 when the request was sent, 1 when another request
// is running and 3 when the PXI send failed.
s32 RTC_GetTimeAsync(void *time, RtcCallback callback, void *callbackArg) {
    u32 savedIrq = OS_DisableInterrupts();

    if (data_02129d50.busy != 0) {
        OS_RestoreInterrupts(savedIrq);
        return 1;
    }
    data_02129d50.busy = 1;
    OS_RestoreInterrupts(savedIrq);
    data_02129d50.command = 1;
    data_02129d50.stage = 0;
    data_02129d50.timeBuffer = time;
    data_02129d50.callback = callback;
    data_02129d50.callbackArg = callbackArg;
    if (RTCi_ReadRawTimeAsync() != 0) {
        return 0;
    }
    data_02129d50.busy = 0;
    return 3;
}

// RTCi_SetRegAdjust(time) (0x0201a430): synchronous wrapper around RTC_GetTimeAsync.
s32 RTCi_SetRegAdjust(void *time) {
    s32 result = RTC_GetTimeAsync(time, RtcGetResultCallback, NULL);

    data_02129d50.result = result;
    if (result == 0) {
        MicWaitBusy();
    }
    return data_02129d50.result;
}
