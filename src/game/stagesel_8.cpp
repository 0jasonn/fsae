#include "engine/functions.h"
#include "game/stageseldecls.h"

// stagesel_message, 0x0207a790. Stage select message sequence: data_0212c4dc 0 opens the message, 1 waits for the
// message frames to finish and then starts the selection. Runs once per frame.
ARM void stagesel_message(void) {
    SselMessageTimes times = data_020dc690;
    if (CommFrameSync() == 0) {
        return;
    }
    CommUpdateJoy();
    *(u32 *)(data_0212c9a8 + 0x3c) = 1;
    del_please_wait();
    switch (data_0212c4dc) {
    case 0:
        stagesel_dialogDisp((u8)*(u16 *)(data_021349c0 + 6), 0);
        data_0212c4dc++;
        break;
    case 1:
        *(u16 *)(data_021349c0 + 4) = *(u16 *)(data_021349c0 + 4) + 1;
        if (*(u16 *)(data_021349c0 + 4) == times.frames[*(u16 *)(data_021349c0 + 6)]) {
            stagesel_dialogDelete();
            ObjMoveInit();
            ObjWorkPoolClear();
            if (data_021349c0[0x0a] != 0) {
                GetSetWork(0x46, 2, 0);
                GetSetWork(0x46, 3, 0);
                GetSetWork(0x46, 4, 0);
            }
            if (*(u16 *)(data_021349c0 + 6) == 0) {
                start_select(0);
            } else {
                start_select(1);
            }
        }
        break;
    }
    data_0212c564();
    func_020830ec();
    CommFrameUpdate();
}
