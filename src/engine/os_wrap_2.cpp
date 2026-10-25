#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sdk_wrap.h"

extern "C" u32 Os_IrqCallbackWrap(u32 unused, u32 b, u32 c, u32 d);

// Calls OSi_IrqCallback with a zero first argument.
ARM u32 Os_IrqCallbackWrap(u32 unused, u32 b, u32 c, u32 d) {
    return OSi_IrqCallback(0, b, c, d);
}
