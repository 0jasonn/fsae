#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"

// PMi_SetDispOffCount() (0x0201d7b4): remembers the current VBlank counter (0x02fffc3c) in the PM state, as the time
// the display was switched off.
void PMi_SetDispOffCount(void) {
    data_0212b920.unk_10 = *(volatile u32 *)0x02fffc3c;
}
