#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sdk_wrap.h"

extern "C" u32 Engine_Relay0201a070(u32 a, u32 b, u32 c, u32 d);

// Tail call to func_0201a070 (not matched yet; keeps its dsd name).
ARM u32 Engine_Relay0201a070(u32 a, u32 b, u32 c, u32 d) {
    return func_0201a070(a, b, c, d);
}
