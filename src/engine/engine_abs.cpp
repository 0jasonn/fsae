#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/engine_abs_api.h"

// Signed absolute value helper (engine, no original name; was AbsS32). Returns |value|.

s32 AbsS32(s32 value) {
    return value < 0 ? -value : value;
}
