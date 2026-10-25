#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sdk_wrap.h"

extern "C" u32 Os_InitCommonWrap(u32 a, u32 b, u32 c, u32 d);

// Tail call to OSi_InitCommon.
ARM u32 Os_InitCommonWrap(u32 a, u32 b, u32 c, u32 d) {
    return OSi_InitCommon(a, b, c, d);
}
