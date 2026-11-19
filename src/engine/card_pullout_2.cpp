#include "engine/functions.h"
#include "engine/card.h"

// Returns the current card pull-out state.

s32 CARD_GetPulledOutFlag(void) {
    return data_0217e2c0.pulledOut;
}
