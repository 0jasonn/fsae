#include "engine/functions.h"
#include "global.h"
#include "types.h"

// SinglePlay callback that returns 0 (0x02096e40, invented name).
extern "C" s32 Knife_Single_SinglePlay_returnZero_02096e40(void);
ARM s32 Knife_Single_SinglePlay_returnZero_02096e40(void) {
    return 0;
}
