#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Clears two words.
void Menu_ClearPair(u32 *pair) {
    pair[0] = 0;
    pair[1] = 0;
}

// Empty hook (no work).
void Menu_NoOp2(void) {
}
