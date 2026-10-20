#include "engine/functions.h"
#include "game/stageseldecls.h"

// stagesel_init0, 0x0207868c. Stage select setup, run once per frame by the state in data_0212c4dc:
// 0 loads the graphics, 1 waits for the wireless check, 2 waits for the partner and sets their player flags.
ARM void stagesel_init0(void) {
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
        *(u16 *)(data_021349c0 + 4) = 0xa;
        *(u16 *)(data_021349c0 + 6) = 0;
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
            *(u16 *)(data_021349c0 + 4) = 0;
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
            *(u32 *)(data_0212c9a8 + 0x3c) = 1;
        }
        for (i = 0; i < data_0212c7c8.unk_0; i++) {
            if (*(u32 *)(data_0212c9a8 + i * 0x34 + 0xa4) == 1) {
                *(u32 *)((u8 *)&data_0212c7c8 + i * 8 + 0x28) |= 0x1000;
            }
        }
        timer = *(u16 *)(data_021349c0 + 4);
        *(u16 *)(data_021349c0 + 4) = timer + 1;
        if (timer <= 8) {
            return;
        }
        partnerCount = data_0212c500;
        *(u16 *)(data_021349c0 + 4) = 0;
        data_0212c500 = partnerCount + 1;
        data_0212c4dc = 0;
        return;
    }
    }
}
