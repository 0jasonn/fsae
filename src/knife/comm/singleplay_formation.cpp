#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"
#include "knife/comm/single_play.h"
#include "knife/comm/single_play_api.h"
#include "knife/comm/singleplay_2.h"
extern u8 data_0211b298[]; // rodata block of tuning values; see singleplay_2.h

// Knife::Single::SinglePlay::UpdateFormationMode2p(SinglePlayWork&) (0x02096110): the two-player formation state machine.
// Returns FALSE on every path. From state 0 it moves to state 0x11 or 0x12 when entity 0 or player 0 is in the right state
// (and copies the table value at data_0211b298+0x32), or, when the palette index matches and the near flag is set, starts
// the formation change (controller 0, PlayerChange, InitializeFormation, the position of entity 1). From state 0x11 or 0x12
// it moves to state 1 and resets the log list once the near flag is clear.

BOOL Knife_Single_SinglePlay_UpdateFormationMode2p(void *self, SpWorkPair *pair) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    switch (sp->unk_0a) {
    case 0:
        if (pair->nearFlag == 0 || pair->entity1->action == 6) {
            goto palette;
        }
        if (pair->entity0->action == 6 && pair->entity0->subAction == 0) {
            sp->unk_24 = *(u16 *)(data_0211b298 + 0x32);
            sp->unk_0a = 0x11;
            sp->unk_26 = pair->entity0->animationState;
        } else if (pair->player0->state == 6) {
            sp->unk_24 = *(u16 *)(data_0211b298 + 0x32);
            sp->unk_0a = 0x12;
            sp->unk_26 = pair->entity0->animationState;
        } else {
            goto palette;
        }
        break;
    palette:
        if ((s32)pair->player0->unk_24 - 0x176 != ((PalBits *)&pair->player0->paletteBits)->b) {
            break;
        }
        if (pair->nearFlag == 0) {
            break;
        }
        sp->contNo = 0;
        sp->flags07 |= 1;
        sp->unk_1a = (pair->unk_18 & ~pair->unk_1a) & 0x803;
        Knife_Single_SinglePlay_SinglePlayWork_PlayerChange(pair);
        Knife_Single_SinglePlay_InitializeFormation(self);
        pair->unk_20 = pair->entity1->x.HALF.HI;
        pair->unk_22 = pair->entity1->y.HALF.HI;
        pair->unk_1e = 0;
        break;
    case 0x11:
    case 0x12:
        if (pair->nearFlag == 0) {
            sp->unk_0a = 1;
            _ZN5Knife6Single10SinglePlay17SinglePlayLogList10InitializeEv((u8 *)self + 0x34);
        }
        break;
    }
    return FALSE;
}
