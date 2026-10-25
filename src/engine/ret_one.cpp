#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u32 Stub_ReturnOne(void);

// Returns 1.
ARM u32 Stub_ReturnOne(void) {
    return 1;
}
