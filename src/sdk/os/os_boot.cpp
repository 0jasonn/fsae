#include "global.h"
#include "types.h"
#include "sdk/os/os_boot.h"

u32 OS_GetBootType(void) {
    return *(u16 *)OS_GetBootInfo();
}

void *OS_GetBootInfo(void) {
    return (void *)0x02fffc40;
}
