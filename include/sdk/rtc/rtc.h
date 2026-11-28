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

// Raw date as the ARM7 leaves it in the shared area at 0x02fffde8 (BCD digits).
typedef struct RtcRawDate {
    u32 year : 8;   // 0
    u32 month : 5;  // 8
    u32 unk_0d : 3; // 13
    u32 day : 6;    // 16
    u32 unk_16 : 2; // 22
    u32 week : 3;   // 24
    u32 unk_1b : 5; // 27
} RtcRawDate;

// Raw time at 0x02fffdec: the current time (time view) or an alarm setting (alarm view, with an enable bit per field).
typedef union RtcRawTime {
    struct {
        u32 hour : 6;
        u32 unk_06 : 2;
        u32 minute : 7;
        u32 unk_0f : 1;
        u32 second : 7;
        u32 unk_17 : 9;
    } time;
    struct {
        u32 week : 3;
        u32 unk_03 : 4;
        u32 weekEnable : 1;
        u32 hour : 6;
        u32 unk_0e : 1;
        u32 hourEnable : 1;
        u32 minute : 7;
        u32 minuteEnable : 1;
        u32 unk_18 : 8;
    } alarm;
} RtcRawTime;

// Raw status register 2 at 0x02fffdea.
typedef struct RtcRawStatus {
    u16 intrMode : 4;
    u16 unk_04 : 2;
    u16 flag6 : 1;
    u16 unk_07 : 9;
} RtcRawStatus;

#define RTC_RAW_DATE (*(RtcRawDate *)0x02fffde8)
#define RTC_RAW_TIME (*(RtcRawTime *)0x02fffdec)

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
