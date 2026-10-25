#include "engine/functions.h"
#include "global.h"

extern "C" s32 func_020c0d6c(void *obj, s32 mask, s32 value, s32 flag, s32 extra);

// SndSys_CheckValue: returns 1 when func_020c0d6c with mask 0xff, flag 1 and no extra value returns zero.
extern "C" s32 SndSys_CheckValue(void *obj, s32 value);
ARM s32 SndSys_CheckValue(void *obj, s32 value) {
    return func_020c0d6c(obj, 0xff, value, 1, 0) == 0;
}
