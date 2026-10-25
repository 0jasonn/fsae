#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u32 Obj_CodeForArgAlt(u32 unused, u32 arg);

// Returns 4 when arg is 1, otherwise 0x102 (the second argument is in r1).
ARM u32 Obj_CodeForArgAlt(u32 unused, u32 arg) {
    if (arg == 1) {
        return 4;
    }
    return 0x102;
}
