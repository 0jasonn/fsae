#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Wraps the value into the range between a and b (the lower end is the smaller of the two): a value below the lower
// end gains the range, a value at or above the upper end loses it. The first argument is the caller object (unused).
ARM s32 Menu_WrapInto(void *self, s32 value, s32 a, s32 b) {
    s32 range;
    s32 swap;

    range = b - a;
    if (range < 0) {
        swap = a;
        a = b;
        b = swap;
        range = swap - a;
    }
    if (value < a) {
        value += range;
    } else if (value >= b) {
        value -= range;
    }
    return value;
}

// Clamps the value into [low, high].
ARM s32 Menu_ClampValue(void *self, s32 value, s32 low, s32 high) {
    if (value < low) {
        value = low;
    } else if (value > high) {
        value = high;
    }
    return value;
}

// Nonzero when low <= value < high.
ARM s32 Menu_InRange(void *self, s32 value, s32 low, s32 high) {
    if (value >= low && value < high) {
        return 1;
    }
    return 0;
}
