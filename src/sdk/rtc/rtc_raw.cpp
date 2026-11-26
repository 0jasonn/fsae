#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/rtc/rtc.h"

// Raw requests: both send one command byte to the ARM7 RTC service.
s32 RTCi_ReadRawTimeAsync(void) {
    return RtcexSendPxiCommand(0x12);
}

s32 RTCi_WriteRawStatus2Async(void) {
    return RtcexSendPxiCommand(0x27);
}

// RtcexSendPxiCommand(command) (0x0201a968): returns 1 when the command word was queued on the RTC FIFO tag.
s32 RtcexSendPxiCommand(u32 command) {
    s32 queued = 0;

    if (PXI_SendWordByFifo(5, (command << 8) & 0x7f00, 0) >= 0) {
        queued = 1;
    }
    return queued;
}

// RTC_GetDayOfWeek(date) (0x0201a994): Zeller-style weekday (0 = Sunday) of a year since 2000, month and day.
s32 RTC_GetDayOfWeek(RtcDate *date) {
    s32 year = date->year + 2000;
    s32 month = date->month - 2;
    s32 day = date->day;

    if (month < 1) {
        year--;
        month += 12;
    }
    return (day + (month * 26 - 2) / 10 + year % 100 + year % 100 / 4 + year / 100 / 4 + year / 100 * 5) % 7;
}
