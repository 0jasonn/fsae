#include "global.h"
#include "types.h"
#include "sdk/os/os_tick.h"

u16 OS_GetTickLo(void) {
    return *(volatile u16 *)0x04000100;
}
