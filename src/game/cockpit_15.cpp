#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Cockpit (HUD), fifteenth unit: CockpitScreenSwap (0x02026788).

// Swaps the screen page of the cockpit when it was requested.
void CockpitScreenSwap(void) {
    if (cockpitState.redraw == 0) {
        return;
    }
    cockpitState.redraw = 0;
    displayState.bg[0].transRequest = 1;
    displayState.bg[0].buffer = data_021361a0 + (cockpitState.bufferIndex << 11);
    cockpitState.bufferIndex ^= 1;
}
