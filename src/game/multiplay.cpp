#include "engine/functions.h"
#include "game/multiplay.h"
#include "global.h"

// multiplay_* and the start of makemap (0x02047478 to 0x02047838).

// Bumps the state byte; the multiplay dummy task only advances the phase counter.
ARM void multiplay_dummy(void) {
    data_0212c500++;
}
