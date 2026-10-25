#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sdk_wrap.h"

extern "C" u32 Os_DoUnlockByWordWrap(u32 a, u32 b, u32 c, u32 unused);

// Calls OSi_DoUnlockByWord with a zero fourth argument.
ARM u32 Os_DoUnlockByWordWrap(u32 a, u32 b, u32 c, u32 unused) {
    return OSi_DoUnlockByWord(a, b, c, 0);
}
