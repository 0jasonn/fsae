#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module cockpit, original names from the debug build): CockpitOff

// Turns the cockpit state off: flags in the cockpit block, the screen layer is set to 3.
void CockpitOff(void) {
    cockpitState[0] = 0;
    cockpitState[2] = 1;
    cockpitState[1] = 0;
    cockpitState[4] = 3;
}
