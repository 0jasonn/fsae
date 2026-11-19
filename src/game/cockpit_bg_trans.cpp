#include "engine/functions.h"
#include "global.h"
#include "game/cockpit_bg_trans.h"

// Functions in this file: cockpit_bg_trans (0x020272d8).

// Transfers the background page when it is requested, otherwise adds the current page to the pending pages.
void cockpit_bg_trans(void) {
    if (cockpitState.redraw != 0) {
        bg_trans_body();
        cockpitState.transMask = 1 << cockpitState.bufferIndex;
        return;
    }
    switch (cockpitState.transMask & 3) {
    case 0:
    case 3:
    default:
        return;
    case 1:
    case 2:
        if ((cockpitState.transMask & (1 << cockpitState.bufferIndex)) != 0) {
            return;
        }
        bg_trans_body();
        cockpitState.transMask |= (u8)(1 << cockpitState.bufferIndex);
    }
}
