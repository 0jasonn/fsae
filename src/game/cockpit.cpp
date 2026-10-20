#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file (module cockpit, original names from the debug build): CockpitOff

// Turns the cockpit state off: flags in the cockpit block, the screen layer is set to 3.
ARM void CockpitOff(void) {
    data_0212c618[0] = 0;
    data_0212c618[2] = 1;
    data_0212c618[1] = 0;
    data_0212c618[4] = 3;
}
