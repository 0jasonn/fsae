#ifndef SDK_RTC_RTC_H
#define SDK_RTC_RTC_H

// TwlSDK RTC library: requests to the ARM7 RTC service over the PXI FIFO (tag 5).
#include "types.h"

typedef void (*RtcCallback)(s32 result, void *arg);

// RTC library state at data_02129d50 (0x28 bytes). The original keeps an init flag and the work proper (from +4, the
// lock word) as two statics addressed from one base; dsd names the second one data_02129d54.
typedef struct RtcWork {
    u16 initialized;      // 0x00
    u16 pad_02;           // 0x02
    s32 busy;             // 0x04: an asynchronous request is in flight (the lock word)
    RtcCallback callback; // 0x08
    void *timeBuffer;     // 0x0c: where the finished request stores the time
    s32 unk_10;           // 0x10
    void *callbackArg;    // 0x14
    s32 command;          // 0x18: 1 = read time
    s32 stage;            // 0x1c
    s32 unk_20;           // 0x20
    s32 result;           // 0x24: result stored by RtcGetResultCallback for the synchronous wrappers
} RtcWork;

// Calendar date as read by RTC_GetDayOfWeek: years since 2000, month 1-12, day 1-31.
typedef struct RtcDate {
    s32 year;
    s32 month;
    s32 day;
} RtcDate;

extern RtcWork data_02129d50;
extern volatile s32 data_02129d54; // data_02129d50.busy, named on its own by dsd (MicWaitBusy reaches it directly)

extern "C" {
void RTC_Init(void);
s32 RTC_GetTimeAsync(void *time, RtcCallback callback, void *callbackArg);
s32 RTCi_SetRegAdjust(void *time);
s32 *Engine_GetBlockD54(void);
void RtcGetResultCallback(s32 result, void *arg);
u32 RtcBCD2HEX(u32 bcd);
s32 RTCi_ReadRawTimeAsync(void);
s32 RTCi_WriteRawStatus2Async(void);
s32 RtcexSendPxiCommand(u32 command);
s32 RTC_GetDayOfWeek(RtcDate *date);
void MicWaitBusy(void);

// Not decompiled yet.
void RtcCommonCallback(u32 tag, u32 data, s32 err);
}

#endif
