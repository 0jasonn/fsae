#include "global.h"
#include "types.h"
#include "sdk/rtc/rtc.h"

extern "C" s32 RTCEXi_CommonCallback(void);

// Finishes an RTC request with the data the ARM7 left in shared memory (0x02fffdec): command 0x10 reads three bytes,
// 0x11 a halfword, 0x12 needs nothing. Any other command clears the stage and returns 4.
s32 RTCEXi_CommonCallback(void) {
    s32 *work;
    s32 status;
    u8 *shared;

    work = Engine_GetBlockD54();
    status = 0;
    switch (work[5]) {
    case 0x10:
        shared = (u8 *)0x02fffdec;
        *(u32 *)work[2] = shared[0] | (shared[1] << 8) | (shared[2] << 16);
        break;
    case 0x11:
        *(u16 *)work[2] = *(u16 *)0x02fffdec;
        break;
    case 0x12:
        break;
    default:
        work[6] = status;
        status = 4;
        break;
    }
    return status;
}
