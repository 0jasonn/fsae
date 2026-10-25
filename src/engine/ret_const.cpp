#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u32 Obj_CodeForArg(u32 unused, u32 arg);
extern "C" u32 Stub_ReturnFourA(void);
extern "C" u32 Stub_ReturnFourB(void);

// Returns 4 when arg is 1, otherwise 0x102 (the second argument is in r1).
ARM u32 Obj_CodeForArg(u32 unused, u32 arg) {
    if (arg == 1) {
        return 4;
    }
    return 0x102;
}

// Returns 4.
ARM u32 Stub_ReturnFourA(void) {
    return 4;
}

// Returns 4.
ARM u32 Stub_ReturnFourB(void) {
    return 4;
}
