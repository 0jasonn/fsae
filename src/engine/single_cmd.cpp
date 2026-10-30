#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

// Knife::Single::SinglePlay move requests and the pending command, 0x02099704 to 0x02099864. The object is the SinglePlay
// singleton; the fields are read at their offsets, with the width of the original access.
#define SP_U8(self, off) (*(u8 *)((u8 *)(self) + (off)))
#define SP_S16(self, off) (*(s16 *)((u8 *)(self) + (off)))
#define SP_PTR(self, off) (*(void **)((u8 *)(self) + (off)))

extern "C" void Knife_Single_SinglePlay_ChangeContPlayerDirect(void *self);
extern "C" void Knife_Single_SinglePlay_SetContNoDirect(void *self, u8 no);
extern "C" void Knife_Single_SinglePlay_SetFormationNoDirect(void *self, u8 no);
extern "C" void Knife_Single_SinglePlay_ChangeFormationNoDirect(void *self);
extern "C" void Knife_Single_SinglePlay_SetObjMoveReqNo(void *self, void *obj, u8 player, s32 delta, u8 dir);

// SinglePlay::SetObjMoveReqNo (0x02099774): for the controlling player (contNo), moves obj by delta in the direction
// given by bits 3 and 4 of dir (x or y, plus or minus). Records obj at 0x30 whenever the move is applied.
extern "C" void Knife_Single_SinglePlay_SetObjMoveReqNo(void *self, void *obj, u8 player, s32 delta, u8 dir);
ARM void Knife_Single_SinglePlay_SetObjMoveReqNo(void *self, void *obj, u8 player, s32 delta, u8 dir) {
    if (delta == 0) {
        return;
    }
    if (player != SP_U8(self, 0x00)) {
        return;
    }
    switch ((dir >> 3) & 3) {
    case 0:
        SP_S16(self, 0x2e) = SP_S16(self, 0x2e) - (s16)delta;
        break;
    case 1:
        SP_S16(self, 0x2c) = SP_S16(self, 0x2c) + (s16)delta;
        break;
    case 2:
        SP_S16(self, 0x2e) = SP_S16(self, 0x2e) + (s16)delta;
        break;
    case 3:
        SP_S16(self, 0x2c) = SP_S16(self, 0x2c) - (s16)delta;
        break;
    }
    SP_PTR(self, 0x30) = obj;
}

