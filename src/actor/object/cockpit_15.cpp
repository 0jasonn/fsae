#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Cockpit (HUD), fifteenth unit: CockpitScreenSwap (0x02026788).

// Swaps the screen page of the cockpit when it was requested.
void CockpitScreenSwap(void) {
    if (cockpitState[2] == 0) {
        return;
    }
    cockpitState[2] = 0;
    *(u16 *)(displayState + 0xe) = 1;
    *(u32 *)(displayState + 0x10) = (u32)(data_021361a0 + (cockpitState[3] << 11));
    cockpitState[3] ^= 1;
}
