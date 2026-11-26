#include "global.h"
#include "types.h"
#include "engine/functions.h"
#include "sdk/os/os_owner_info.h"

// Copies the 6-byte console MAC address from the shared header area.
void OS_GetMacAddress(u8 *dest) {
    MI_CpuCopy8((const void *)0x02fffcf4, dest, 6);
}
