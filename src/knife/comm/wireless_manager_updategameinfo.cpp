#include "engine/functions.h"
#include "knife/comm/wireless_manager_c.h"

// Knife::Comm::WirelessManager::updateUserGameInfo() (0x02091eb4): fills the "KNF" game-info block with the
// current user value and link level and pushes it through WM_SetGameInfo.
// The file also emits the WmInterruptSection destructor (0x02090e80) as an out-of-line copy of the inline class
// destructor declared in knife/comm/wireless_manager_c.h (it matches the ROM's _ZN18WmInterruptSectionD1Ev).

BOOL Knife_Comm_WirelessManager_updateUserGameInfo(void *self) {
    WmInterruptSection section;
    WmCWork *wm = (WmCWork *)self;
    s32 linkLevel;
    u16 isFlag;
    u32 paramD;
    u16 paramA;
    s32 flag;

    if (wm->state != 8) {
        return FALSE;
    }
    if (func_02090ecc(self) != 0) {
        return FALSE;
    }
    wm->gameInfo.magic = 0x464e4b;
    wm->gameInfo.value = wm->userValue;
    linkLevel = Knife_Comm_WirelessManager_getLinkLevel(self);
    wm->gameInfo.linkLevel = linkLevel - 1;
    isFlag = wm->isFlag;
    paramD = wm->paramD;
    flag = isFlag != 0;
    paramA = wm->paramA;
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_SetGameInfo(Knife_Comm_WirelessManager_callback_WM_ClearFlag, &wm->gameInfo, paramA, 0x800602, paramD, flag), 0, data_0211b18c)) {
        return FALSE;
    }
    wm->unk_1cdc = 1;
    return TRUE;
}
