#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/stub_zero_a_api.h"

// SinglePlay callback that returns 0 (0x020956ec, invented name).
s32 Knife_Single_SinglePlay_returnZero_020956ec(void) {
    return 0;
}
