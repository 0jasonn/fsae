#include "engine/functions.h"
#include "knife/comm/single_play.h"
#include "knife/comm/singleplay_command.h"

extern "C" {
}

// Knife::Single::SinglePlay::UpdateCommand(PL_WORK_*, PL_WORK_*) (0x020997fc): runs the pending request. Kind 1 changes the
// controller (a number below 2 selects it, anything else switches to the other one), kind 2 the formation (a number below 5
// selects it, anything else steps to the next one). The request is cleared afterwards.
void Knife_Single_SinglePlay_UpdateCommand(void *self, PlayerData *player0, PlayerData *player1) {
    SinglePlayWork *work = (SinglePlayWork *)self;
    u8 no;

    switch (work->reqKind) {
    case 1:
        if (work->reqNo < 2) {
            Knife_Single_SinglePlay_SetContNoDirect(self, work->reqNo);
        } else {
            Knife_Single_SinglePlay_ChangeContPlayerDirect(self);
        }
        break;
    case 2:
        no = work->reqNo;
        if (no < 5) {
            Knife_Single_SinglePlay_SetFormationNoDirect(self, no);
        } else {
            Knife_Single_SinglePlay_ChangeFormationNoDirect(self, player0, player1);
        }
        break;
    }
    work->reqKind = 0;
    work->reqNo = 0;
}
