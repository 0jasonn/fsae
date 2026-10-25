#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// os_owner: function OS_getOwnerFlag (0x020b7b00), matching. It reads the owner information block (0x54 bytes) and
// returns its second byte.

extern "C" void OS_GetOwnerInfo(void *info);

// OS_getOwnerFlag() (0x020b7b00, provisional name): returns byte 1 of the owner information
extern "C" u8 OS_getOwnerFlag(void);
ARM u8 OS_getOwnerFlag(void) {
    u8 info[0x54];

    OS_GetOwnerInfo(info);
    return info[1];
}
