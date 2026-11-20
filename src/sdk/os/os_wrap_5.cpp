#include "engine/functions.h"
#include "global.h"
#include "types.h"

// TODO(headers): this declaration of OS_WaitEventEx differs from the shared one; see the header restructure report.
extern "C" u32 OS_WaitEventEx(u32 a, u32 b, u32 c, u32 d);

extern "C" u32 Os_WaitEventExWrap(u32 a, u32 b, u32 c, u32 unused);

// Calls OS_WaitEventEx with a zero fourth argument.
u32 Os_WaitEventExWrap(u32 a, u32 b, u32 c, u32 unused) {
    return OS_WaitEventEx(a, b, c, 0);
}
