#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_owner_info.h"
#include "sdk/wm/wm_system.h"

// WM_GetDispersionBeaconPeriod() (0x0201f69c): beacon period (200 plus a 0-19 offset) derived from the MAC address and
// the VBlank counter, so that nearby parents do not beacon in lockstep.
u16 WM_GetDispersionBeaconPeriod(void) {
    u8 mac[6];
    u16 sum;
    s32 i;
    u16 value;

    OS_GetMacAddress(mac);
    sum = i = 0;
    for (; i < 6; i++) {
        sum += mac[i];
    }
    value = sum + (u16) * (volatile u32 *)0x02fffc3c;
    value = value * 7;
    return 200 + value % 20;
}

// WM_GetDispersionScanPeriod() (0x0201f730): scan period (30 plus a 0-9 offset) derived the same way.
s32 WM_GetDispersionScanPeriod(void) {
    u8 mac[6];
    s32 i;
    u16 sum;
    u16 value;

    OS_GetMacAddress(mac);
    sum = i = 0;
    for (; i < 6; i++) {
        sum += mac[i];
    }
    value = sum + (u16) * (volatile u32 *)0x02fffc3c;
    value = value * 13;
    return (u16)(30 + value % 10);
}
