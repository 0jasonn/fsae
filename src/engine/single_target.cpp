#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

// SinglePlay work item (the SinglePlayWork of single_play_d.h) fields used by SetTargetPos, read at their widths.
#define SP_S16(self, off) (*(s16 *)((u8 *)(self) + (off)))
#define SP_PTR(self, off) (*(void **)((u8 *)(self) + (off)))

// abs_s32 (0x02029a44): the absolute value of a long (C++ linkage).
s32 abs_s32(s32 value);

// SinglePlayWork::SetTargetPos (0x02099f5c): the offset of the entity at 0x14 from the work item's origin, stored at
// 0x2c and 0x2e, and the absolute values (abs_s32) at 0x30 and 0x32.
extern "C" void Knife_Single_SinglePlay_SinglePlayWork_SetTargetPos(void *self);
ARM void Knife_Single_SinglePlay_SinglePlayWork_SetTargetPos(void *self) {
    SP_S16(self, 0x2c) = SP_S16(self, 0x20) - SP_S16(SP_PTR(self, 0x14), 0x32);
    SP_S16(self, 0x2e) = SP_S16(self, 0x22) - SP_S16(SP_PTR(self, 0x14), 0x36);
    SP_S16(self, 0x30) = (s16)abs_s32(SP_S16(self, 0x2c));
    SP_S16(self, 0x32) = (s16)abs_s32(SP_S16(self, 0x2e));
}
