#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u32 Stub_ReturnZeroB(u32 a, u32 b, u32 c, u32 d);

// Returns 0.
ARM u32 Stub_ReturnZeroB(u32 a, u32 b, u32 c, u32 d) {
    return 0;
}
