#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/rtc/rtc.h"

// RtcBCD2HEX(bcd) (0x0201a8b8): converts eight packed BCD digits to a number; returns 0 when a nibble is not a decimal digit.
u32 RtcBCD2HEX(u32 bcd) {
    u32 value = 0;
    u32 scale;
    u32 digit;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (((bcd >> (i * 4)) & 0xf) >= 10) {
            return 0;
        }
    }
    i = 0;
    scale = 1;
    for (; i < 8; i++) {
        digit = (bcd >> (i * 4)) & 0xf;
        value += scale * digit;
        scale *= 10;
    }
    return value;
}

// RtcGetResultCallback(result, arg) (0x0201a920): completion callback of the synchronous wrappers; stores the result.
void RtcGetResultCallback(s32 result, void *arg) {
    data_02129d50.result = result;
}
