#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/std/std_snprintf_api.h"

// STD_TSPrintf(dst, fmt, ...) (0x0201dc68): unbounded sprintf, a variadic wrapper of STD_TVSNPrintf with the maximum
// size. The variadic arguments follow fmt in the caller's stack words.
s32 STD_TSPrintf(char *dst, const char *fmt, ...) {
    return STD_TVSNPrintf(dst, 0x7fffffff, fmt, (u8 *)(((u32)&fmt) & ~3) + 4);
}
