#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/device_flags_api.h"

// Device flags at data_020dfb9c (+4): -1 until the first query.
typedef struct DeviceFlags {
    u32 unk_00;
    u32 flags;
} DeviceFlags;

extern DeviceFlags data_020dfb9c;

// Device_InitFlags() (0x02017f64): on the first call sets the flags to 0x1800004 and ors in the detected device type.
void Device_InitFlags(void) {
    if (data_020dfb9c.flags != 0xffffffff) {
        return;
    }
    data_020dfb9c.flags = 0x1800004;
    data_020dfb9c.flags |= OSi_DetectDeviceType();
}
