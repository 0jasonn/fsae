#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit.h"

// Functions in this file: func_02026774 (dsd name, declared in functions.h)

// Sets the flag that requests a redraw of the cockpit.
ARM void func_02026774(void) {
    data_0212c618[2] = 1;
}
