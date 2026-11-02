#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"
#include "knife/comm/single_play.h"
#include "knife/comm/single_play_api.h"
#include "knife/comm/singleplay_work_api.h"
#include "knife/comm/singleplay_d.h"

// Knife::Single::SinglePlay::UpdatePause(PL_WORK_*, PL_WORK_*) (0x02093ef4): builds the work pair on the stack, sets the
// palette bits of the two players, then waits for the partner or ends a controller change, and clears the pause state.

void Knife_Single_SinglePlay_UpdatePause(void *self, PlayerData *player0, PlayerData *player1) {
    SpWorkPair pair;
    u8 contNo;

    Knife_Single_SinglePlay_SinglePlayWork_SinglePlayWork(&pair);
    contNo = ((SinglePlayWork *)self)->contNo;
    *(u16 *)((u8 *)self + 0x14) = 0;
    *(u16 *)((u8 *)self + 0x16) = 0;
    ((SinglePlayWork *)self)->formationChanging = 0;
    ((SinglePlayWork *)self)->flags07 = 0;
    Knife_Single_SinglePlay_SinglePlayWork_Initialize(&pair, contNo, player0, player1);

    ((PalBits *)&pair.player1->paletteBits)->a = 0;
    ((PalBits *)&pair.player0->paletteBits)->a = ((PalBits *)&pair.player1->paletteBits)->a;
    ((PalBits *)&pair.player0->paletteBits)->c = ((PalBits *)&pair.player0->paletteBits)->c << 1;
    ((PalBits *)&pair.player1->paletteBits)->c = ((PalBits *)&pair.player1->paletteBits)->c << 1;

    pair.player1->unk_31 = 0;
    pair.player0->unk_31 = pair.player1->unk_31;
    if (((SinglePlayWork *)self)->contChanging != 0) {
        if (frameCounter[0x13] != 0) {
            Knife_Single_SinglePlay_SetContNoDirect(self, ((SinglePlayWork *)self)->contNo);
        }
    } else {
        Knife_Single_SinglePlay_UpdateWaitPartner(self, pair.player0, pair.player1);
    }

    ((SinglePlayWork *)self)->unk_0d[0] = 0;
    ((SinglePlayWork *)self)->unk_2e = 0;
    ((SinglePlayWork *)self)->unk_2c = 0;
    ((SinglePlayWork *)self)->unk_30 = NULL;
    ((SinglePlayWork *)self)->unk_12 = 0;
    ((SinglePlayWork *)self)->unk_1a = 0;
    *(u16 *)((u8 *)self + 0x16) = 0;
}
