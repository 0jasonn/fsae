#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Absolute value (abs_s32, provisional name abs_s32).
ARM s32 abs_s32(s32 value) {
    if (value < 0) {
        value = -value;
    }
    return value;
}
