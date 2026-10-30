#include "engine/functions.h"
#include "global.h"
#include "types.h"

// SinglePlay callback that returns 0 (0x020956ec, invented name).
extern "C" s32 Knife_Single_SinglePlay_returnZero_020956ec(void);
ARM s32 Knife_Single_SinglePlay_returnZero_020956ec(void) {
    return 0;
}
