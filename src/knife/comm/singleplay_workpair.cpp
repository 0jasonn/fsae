#include "engine/functions.h"
#include "knife/comm/singleplay_2.h"
#include "knife/comm/singleplay_pair.h"

// Knife::Single::SinglePlay::SinglePlayWork, the pair work item of the update (0x02099e18 to 0x02099f5c): Initialize
// fills it from the two players, PlayerChange swaps the two sides.

// SinglePlayWork::Initialize(unsigned char, PL_WORK_*, PL_WORK_*) (0x02099e18): stores the players (swapped when the second
// one is the controlled one) and their data blocks, then the entities, their position difference and the near flag
void Knife_Single_SinglePlay_SinglePlayWork_Initialize(void *self, u8 contNo, PlayerData *player0, PlayerData *player1) {
    SpWorkPair *work = (SpWorkPair *)self;

    if (contNo == 0) {
        work->player0 = player0;
        work->player1 = player1;
        work->data0 = data_0212caf0;
        work->data1 = data_0212cb60;
    } else {
        work->player0 = player1;
        work->player1 = player0;
        work->data1 = data_0212caf0;
        work->data0 = data_0212cb60;
    }
    work->entity0 = work->player0->entity;
    work->entity1 = work->player1->entity;
    if (work->entity0 == NULL || work->entity1 == NULL) {
        return;
    }
    work->diffX = work->entity0->x.HALF.HI - work->entity1->x.HALF.HI;
    work->diffY = work->entity0->y.HALF.HI - work->entity1->y.HALF.HI;
    work->distX = abs_s32(work->diffX);
    work->distY = abs_s32(work->diffY);
    if (work->distX < 0x20 && work->distY < 0x20) {
        work->nearFlag = 1;
    }
}

// SinglePlayWork::PlayerChange() (0x02099ed8): swaps the two players and their data blocks, negates the position difference
// and exchanges the low two palette bits of the two players
void Knife_Single_SinglePlay_SinglePlayWork_PlayerChange(void *self) {
    SpWorkPair *work = (SpWorkPair *)self;
    PlayerData *player;
    void *data;
    u8 bits;

    player = work->player0;
    work->player0 = work->player1;
    work->player1 = player;
    data = work->data0;
    work->data0 = work->data1;
    work->data1 = data;
    work->entity0 = work->player0->entity;
    work->entity1 = work->player1->entity;
    work->diffX = -work->diffX;
    work->diffY = -work->diffY;
    bits = work->player0->paletteBits.pairRole;
    work->player0->paletteBits.pairRole = work->player1->paletteBits.pairRole;
    work->player1->paletteBits.pairRole = bits;
}
