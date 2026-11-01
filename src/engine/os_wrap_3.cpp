#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sdk_wrap.h"
#include "engine/os_wrap_api.h"

// Calls OSi_DoLockByWord with a zero fourth argument.
u32 Os_DoLockByWordWrap(u32 a, u32 b, u32 c, u32 unused) {
    return OSi_DoLockByWord(a, b, c, 0);
}
