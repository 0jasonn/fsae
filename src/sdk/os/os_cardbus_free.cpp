#include "global.h"
#include "types.h"
#include "sdk/os/cardbus_lock_api.h"

void OSi_FreeCardBus(void) {
    *(volatile u16 *)0x04000204 |= 0x800;
}
