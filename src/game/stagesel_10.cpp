#include "engine/functions.h"
#include "game/stageseldecls.h"

// stagesel_dialog, 0x0207abb4. Stage select dialog, once per frame. data_0212c4dc 0 waits for the answer of the
// selection dialog (data_02171d7c), 1 waits for the confirmation in the pause dialog.
ARM void stagesel_dialog(void) {
    u16 value;
    if (CommFrameSync() == 0) {
        return;
    }
    CommUpdateJoy();
    value = data_0212c58c[0];
    data_0212c58c[1] = value;
    data_0212c58c[2] = value;
    data_0212c58c[3] = value;
    Knife_Message_selectionDialog_update(data_02171d7c);
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 || localPlayerIndex == 0) {
        ssel_pause_dialogUpdate();
    }
    stagesel_scroll();
    data_0212c564();
    func_020830ec();
    CommFrameUpdate();
    switch (data_0212c4dc) {
    case 0:
        if (Knife_Message_selectionDialog_getResult(data_02171d7c) == 2) {
            data_0212c500 = 4;
            return;
        }
        if (Knife_Message_selectionDialog_getResult(data_02171d7c) != 1) {
            return;
        }
        if ((s8)data_02171d7c[4] == 0) {
            data_0212c500 = 4;
            return;
        }
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
            ssel_pause_dialogDisp(0x900, 4, 0);
        } else {
            ssel_pause_dialogDisp(0x8ff, 6, 0);
        }
        data_0212c4dc = 1;
        return;
    case 1:
        if (Knife_Message_selectionDialog_getResult(data_02171d7c) == 2) {
            ssel_pause_dialogDisp(0x901, 6, 0);
            data_0212c4dc = 0;
            return;
        }
        if (Knife_Message_selectionDialog_getResult(data_02171d7c) != 1) {
            return;
        }
        if ((s8)data_02171d7c[4] == 0) {
            ssel_pause_dialogDisp(0x901, 6, 0);
            data_0212c4dc = 0;
            return;
        }
        data_0212c500 = 0xa;
        data_0212c4dc = 0;
        SoundReq(0x80040000);
        return;
    }
}
