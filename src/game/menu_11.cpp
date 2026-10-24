#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Clears two words.
ARM void Menu_ClearPair(u32 *pair) {
    pair[0] = 0;
    pair[1] = 0;
}

// Empty hook (no work).
ARM void Menu_NoOp2(void) {
}
