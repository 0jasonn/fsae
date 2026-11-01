#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"
#include "engine/os_owner_api.h"

// os_owner: function OS_getOwnerFlag (0x020b7b00), matching. It reads the owner information block (0x54 bytes) and
// returns its second byte.

// OS_getOwnerFlag() (0x020b7b00, provisional name): returns byte 1 of the owner information
u8 OS_getOwnerFlag(void) {
    u8 info[0x54];

    OS_GetOwnerInfo(info);
    return info[1];
}
