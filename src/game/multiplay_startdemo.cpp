#include "engine/functions.h"
#include "game/multiplay.h"
#include "engine/irq.h"
#include "engine/display_state.h"
#include "engine/vblank_request.h"

// multiplay_startdemo() (0x02047b14): the start demo of a multiplayer stage: asks the communication layer for the start
// sync, then clears the frame counters, arms the shared enemy state, sets up the circle/triangle windows and the fade, spawns
// the start actors and plays the start sound.
void multiplay_startdemo(void) {
    switch (data_0212c4dc) {
    case 0:
        ComRequest(4);
        data_0212c4dc++;
        break;
    case 1:
        if (WXC_GetStateCode() != 1) {
            break;
        }
        data_0212c500++;
        data_0212c4dc = 0;
        data_0212c4b8 = 0;
        data_0212c520 = 0;
        frameCounter.frame = 0;
        frameCounter.wipeSize = 0;
        frameState.frameCount = 0;
        frameCounter.timer = 0x78;
        data_0212c550 = data_0212c554;
        ComRequest(5);
        if (gameState.periodicFlag == 0) {
            Enemy_ArmSharedState();
        }
        displayState.displayFlags = displayState.savedFlags | 0x1740;
        InitCircleWindow(0x1f, 0);
        MakeTriangleWindow(0x80, 0x60, 1, 0);
        FadeClear();
        GetSetWork(0x10, 0, 0);
        if (gameState.unk_6d & 1) {
            gameState.unk_6d |= 2;
            GetSetWorkSp(0x2e, 0, 0xf0);
        } else {
            GetSetWorkSp(0x2e, 0, 0);
        }
        MemClearFast(&comWork.next, 0x34);
        SoundReq(0x80010000);
        SoundReq(0x58);
    }
    VGroupManager();
}
