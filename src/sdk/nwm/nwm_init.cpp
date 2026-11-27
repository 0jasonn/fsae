#include "global.h"
#include "types.h"
#include "sdk/nwm/nwm.h"

u32 NWMi_CheckInitialized(void) {
    if (data_021277d4 != 0) {
        return 0;
    }
    return 3;
}
