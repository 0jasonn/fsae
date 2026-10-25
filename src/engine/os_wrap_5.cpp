#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sdk_wrap.h"

extern "C" u32 Os_WaitEventExWrap(u32 a, u32 b, u32 c, u32 unused);

// Calls OS_WaitEventEx with a zero fourth argument.
ARM u32 Os_WaitEventExWrap(u32 a, u32 b, u32 c, u32 unused) {
    return OS_WaitEventEx(a, b, c, 0);
}
