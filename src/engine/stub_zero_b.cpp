#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/stub_zero_b_api.h"

// SinglePlay callback that returns 0 (0x02096e40, invented name).
s32 Knife_Single_SinglePlay_returnZero_02096e40(void) {
    return 0;
}
