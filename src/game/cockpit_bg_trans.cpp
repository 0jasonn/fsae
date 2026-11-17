#include "engine/functions.h"
#include "global.h"
#include "game/cockpit_bg_trans.h"

// Functions in this file: cockpit_bg_trans (0x020272d8).

// Transfers the background page when it is requested, otherwise adds the current page to the pending pages.
void cockpit_bg_trans(void) {
    if (cockpitState[2] != 0) {
        bg_trans_body();
        cockpitState[0xb] = 1 << cockpitState[3];
        return;
    }
    switch (cockpitState[0xb] & 3) {
    case 0:
    case 3:
    default:
        return;
    case 1:
    case 2:
        if ((cockpitState[0xb] & (1 << cockpitState[3])) != 0) {
            return;
        }
        bg_trans_body();
        cockpitState[0xb] |= (u8)(1 << cockpitState[3]);
    }
}
