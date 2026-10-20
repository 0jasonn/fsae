#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpitdata.h"

// Adds delta to value and clamps the result to the limit (the limit is returned when the sum is larger).
ARM s32 add_sub(s32 value, s32 delta, s32 limit) {
    s32 sum;

    sum = value + delta;
    if (sum < 0) {
        return 0;
    }
    if (sum <= limit) {
        limit = sum;
    }
    return limit;
}
