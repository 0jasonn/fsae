#include "engine/functions.h"
#include "global.h"
#include "engine/sound/sndsys_api.h"
#include "engine/menusound.h"


// SndSys_CheckValue: returns 1 when func_020c0d6c with mask 0xff, flag 1 and no extra value returns zero.
s32 SndSys_CheckValue(void *obj, s32 value) {
    return func_020c0d6c((s32)obj, 0xff, (void *)value, 1, 0) == 0;
}
