#include "engine/subtask_status.h"

// GetSubtaskPlayerStatus (0x020a31ac): fills the status block of one player, from the wireless member record in
// wireless mode and from the local send table otherwise.
void GetSubtaskPlayerStatus(int playerIndex, SUBTASK_PLAYER_WORK *status) {
    int floatValue;
    int linkLevel;
    s32 state;
    SubtaskMember *member;
    void *manager;

    floatValue = Fp_PackU32ToFloat(status->floatValue);
    linkLevel = 0;
    MI_CpuFill8(status, 0, 0x14);
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        manager = func_020909c8();
        state = Knife_Comm_WirelessManager_getState(manager);
        if (state == 8 || state == 0xb) {
            linkLevel = Knife_Comm_WirelessManager_getLinkLevel(manager);
        }
        status->linkOk = playerIndex < linkLevel;
        status->isLocal = playerIndex == localPlayerIndex;
        if (!status->linkOk) {
            return;
        }
        member = &data_0212ca20[playerIndex];
        status->flag = member->bits.b0;
        status->bit4 = member->bits.b2;
        status->bit5 = member->bits.b3;
        status->bit6 = member->bits.b4;
        status->bit7 = member->bits.b5;
        status->bit8 = member->bits.b6;
        status->field9 = member->bits.b7;
        status->field11 = member->bits.b9;
        status->field13 = member->bits.b11;
        status->medalValue = member->bits.b13;
        status->ruppyValue = member->w28;
        status->floatValue = member->w2c;
    } else {
        if (playerIndex < 2) {
            linkLevel = 1;
        }
        status->linkOk = linkLevel;
        status->isLocal = 0;
        if (!status->linkOk) {
            return;
        }
        status->flag = subtask_getFlag(playerIndex);
        status->bit4 = (data_021350b0[multiSioSelect.index].word00 & 2) != 0;
        status->bit5 = (data_021350b0[multiSioSelect.index].word00 & 1) != 0;
        status->bit6 = (data_021350b0[multiSioSelect.index].word00 & 0x200) != 0;
        status->bit7 = (data_021350b0[multiSioSelect.index].word00 & 0x400) != 0;
        status->bit8 = (data_021350b0[multiSioSelect.index].word00 & 0x1000) != 0;
        status->field9 = data_021350b0[multiSioSelect.index].b05 >> 2;
        status->field11 = data_021350b0[multiSioSelect.index].b05;
        status->field13 = data_021350b0[multiSioSelect.index].b05 >> 4;
        status->medalValue = data_021350b0[multiSioSelect.index].h06;
        status->ruppyValue = data_021350b0[multiSioSelect.index].w18;
        status->floatValue = func_0200dd38(floatValue);
    }
}
