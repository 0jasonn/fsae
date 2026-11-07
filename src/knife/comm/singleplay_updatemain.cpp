#include "knife/comm/singleplay_a.h"

// Knife::Single::SinglePlay::Update(PL_WORK_*, PL_WORK_*, unsigned short, unsigned short) (0x02093c48): the per-frame
// update of the single play partner logic. Builds the work pair on the stack, runs the pending commands, moves the
// partner (or waits for it) and restores the player heights.
void Knife_Single_SinglePlay_Update(void *self, PlayerData *player0, PlayerData *player1, u16 keysDown, u16 keysHeld) {
    SpWorkPair pair;
    u8 contNo;

    Knife_Single_SinglePlay_SinglePlayWork_SinglePlayWork(&pair);
    if (player0->entity != NULL && player1->entity != NULL) {
        player0->entity->y.HALF.HI -= player0->yOffset;
        player1->entity->y.HALF.HI -= player1->yOffset;
    }
    pair.unk_1c = *(u16 *)((u8 *)self + 0x14);
    pair.unk_18 = keysDown;
    pair.unk_1a = keysHeld;
    *(u16 *)((u8 *)self + 0x14) = 0;
    *(u16 *)((u8 *)self + 0x16) = 0;
    ((SinglePlayWork *)self)->formationChanging = 0;
    ((SinglePlayWork *)self)->flags07 = 0;
    if (Knife_Single_SinglePlay_CheckCommand(self, player0, player1)) {
        Knife_Single_SinglePlay_UpdateCommand(self, player0, player1);
    }
    if (((SinglePlayWork *)self)->flags07 & 4) {
        *(u16 *)((u8 *)self + 0x18) = keysDown;
    }
    Knife_Single_SinglePlay_SinglePlayWork_Initialize(&pair, ((SinglePlayWork *)self)->contNo, player0, player1);

    ((PalBits *)&pair.player1->paletteBits)->a = 0;
    ((PalBits *)&pair.player0->paletteBits)->a = ((PalBits *)&pair.player1->paletteBits)->a;
    ((PalBits *)&pair.player0->paletteBits)->c = ((PalBits *)&pair.player0->paletteBits)->c << 1;
    ((PalBits *)&pair.player1->paletteBits)->c = ((PalBits *)&pair.player1->paletteBits)->c << 1;
    pair.player1->unk_31 = 0;
    pair.player0->unk_31 = pair.player1->unk_31;

    if (pair.entity0 != NULL && pair.entity1 != NULL) {
        if (pair.entity1->y.HALF.HI == pair.entity0->y.HALF.HI) {
            s16 low = pair.entity0->y.HALF.LO;
            if (pair.entity1->y.HALF.LO >= (u16)low) {
                if (low != 0) {
                    pair.entity1->y.HALF.LO = (u16)low - 1;
                } else {
                    *(s16 *)&pair.entity1->y.HALF.LO = low;
                    pair.entity0->y.HALF.LO++;
                }
            }
        }
        ((SinglePlayWork *)self)->unk_10[0] = player0->entity->action;
        ((SinglePlayWork *)self)->unk_10[1] = player1->entity->action;
    }

    if (((SinglePlayWork *)self)->contChanging != 0) {
        Knife_Single_SinglePlay_UpdateMovePartner(self, &pair);
        if (pair.player1->unk_14 == 0) {
            u8 action = pair.entity0->action;
            if (action != 3 && action != 0x11 && action != 0x12) {
                pair.player1->unk_14 = 1;
            }
        }
    } else {
        Knife_Single_SinglePlay_UpdateWaitPartner(self, pair.player0, pair.player1);
    }

    ((SinglePlayWork *)self)->unk_0d[0] = 0;
    ((SinglePlayWork *)self)->unk_2e = 0;
    ((SinglePlayWork *)self)->unk_2c = 0;
    ((SinglePlayWork *)self)->unk_30 = NULL;
    ((SinglePlayWork *)self)->unk_12 = 0;
    if (player0->entity != NULL && player1->entity != NULL) {
        player0->entity->y.HALF.HI += player0->yOffset;
        player1->entity->y.HALF.HI += player1->yOffset;
    }
    ((SinglePlayWork *)self)->unk_1a &= keysDown;
    *(u16 *)((u8 *)self + 0x16) |= ((SinglePlayWork *)self)->unk_1a;
}
