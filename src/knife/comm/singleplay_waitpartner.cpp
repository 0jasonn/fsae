#include "engine/functions.h"
#include "knife/comm/singleplay_2.h"
#include "knife/comm/singleplay_movepartner.h"

// Knife::Single::SinglePlay::UpdateWaitPartner(PL_WORK_*, PL_WORK_*) (0x02099428): clears the move flags, and while the
// second player is idle and the first one is not in a special state asks for the next formation when both hold the same
// object, or else starts the wait pose (player 1 stands still with its palette bits set).
void Knife_Single_SinglePlay_UpdateWaitPartner(void *self, PlayerData *player0, PlayerData *player1) {
    Entity *entity;
    u16 statusFlags;

    player1->nutBits.b6 = 0;
    player0->nutBits.b6 = player1->nutBits.b6;
    ((SinglePlayWork *)self)->unk_05[0] = 0;
    ((SinglePlayWork *)self)->unk_05[1] = 0;
    ((SinglePlayWork *)self)->unk_08 = 0;
    ((SinglePlayWork *)self)->unk_09 = 0;
    ((SinglePlayWork *)self)->unk_0c = 0;
    if (frameCounter.pauseRequest != 0) {
        return;
    }
    if (player0->entity == NULL) {
        return;
    }
    entity = player1->entity;
    if (entity == NULL) {
        return;
    }
    statusFlags = player1->statusFlags;
    if (player0->statusFlags & statusFlags & 0x1000) {
        if (player0->holdObject == player1->holdObject) {
            Knife_Single_SinglePlay_ChangeFormationNo(self);
            return;
        }
    }
    if (player0->unk_07 & 0x80) {
        return;
    }
    if (statusFlags & 0x7f15) {
        return;
    }
    if (player1->unk_0b == 0) {
        if (!(player1->hitFlags & 0x20) && player1->motionId == 0x2c4) {
            if (entity->action != 6) {
                entity->animationState = 4;
                player1->unk_35 = 0xff;
            }
        }
    }
    *(u16 *)((u8 *)self + 0x14) = 0x1000;
    *(u16 *)&player1->unk_8c[2] = 0;
    *(u16 *)&player1->unk_8c[0] = 0;
    ((PalBits *)&player1->paletteBits)->c |= 1;
}
