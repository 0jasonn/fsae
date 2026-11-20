#include "engine/functions.h"
#include "knife/comm/single_play.h"
#include "knife/comm/singleplay_objmove.h"
#include "knife/comm/singleplay_pair.h"

// Knife::Single::SinglePlay::SetObjMoveReqFlag(OBJ_WORK_*, unsigned long, long, unsigned char) (0x02099704): for each
// player bit of mask (players 0 and 1) requests the move of obj through SetObjMoveReqNo. The mask is remembered at +0x12
// when obj is the current mover (or none is set at +0x30).
void Knife_Single_SinglePlay_SetObjMoveReqFlag(void *self, Entity *obj, u32 mask, s32 delta, u8 dir) {
    SinglePlayWork *work = (SinglePlayWork *)self;
    u32 i;

    if (mask == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (mask & (1 << i)) {
            Knife_Single_SinglePlay_SetObjMoveReqNo(self, obj, i, delta, dir);
        }
    }
    if (work->unk_30 == obj || work->unk_30 == NULL) {
        work->unk_12 = mask;
    }
}
