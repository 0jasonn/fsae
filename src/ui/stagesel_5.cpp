#include "engine/functions.h"
#include "ui/stagesel_common.h"

// stagesel_init0, 0x0207868c. Stage select setup, run once per frame by the state in data_0212c4dc:
// 0 loads the graphics, 1 waits for the wireless check, 2 waits for the partner and sets their player flags.
void stagesel_init0(void) {
    switch (data_0212c4dc) {
    case 0: {
        u16 loadIndex = 0x14;
        DispReset();
        CgLoad(0xf);
        DataLoad(loadIndex);
        data_02171d58.unk_10 = loadIndex - 0x15;
        ssel_char_scr(((u8 *)KnifeApp_getInstance())[0xcb0]);
        SetCgColor(0, 0x6739);
        ObjWorkPoolClear();
        ObjMoveInit();
        MessageInitialize();
        data_0212c4dc++;
        data_02171d58.pleaseWait = 0;
        data_02171d58.unk_18 = 0;
        effectState.timer = 0xa;
        effectState.messageIndex = 0;
        data_02171d58.tutorialActive = 0;
        data_02171d58.tutorialTimer = 0;
        ComRequest(4);
        if (data_0212c4d0 == 5) {
            return;
        }
        func_020827a8(5);
        return;
    }
    case 1: {
        if (WXC_GetStateCode() != 1) {
            return;
        }
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
            u8 next = data_0212c4dc + 1;
            effectState.timer = 0;
            data_0212c4dc = next;
            ComRequest(5);
        } else {
            data_0212c4dc = 0;
            data_0212c500++;
        }
        return;
    }
    case 2: {
        int i;
        u16 timer;
        u8 partnerCount;
        if (CommFrameSync() == 0) {
            return;
        }
        if ((enemyTypeFlags[localPlayerIndex].flags & 0x1000) != 0) {
            comWork.send.stageFlag = 1;
        }
        for (i = 0; i < gameState.playerCount; i++) {
            if (comWork.recv[i].stageFlag == 1) {
                gameState.slots[i].flags |= 0x1000;
            }
        }
        timer = effectState.timer;
        effectState.timer = timer + 1;
        if (timer <= 8) {
            return;
        }
        partnerCount = data_0212c500;
        effectState.timer = 0;
        data_0212c500 = partnerCount + 1;
        data_0212c4dc = 0;
        return;
    }
    }
}
