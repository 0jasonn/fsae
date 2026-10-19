#include "engine/functions.h"
#include "enemy/ending.h"
#include "global.h"

// Implementer B, round 6: finale_wait (0x02045308), finale_demo (0x0204537c).

// finale_wait (0x02045308): waits for the link state, then starts the staff roll fade.
ARM void finale_wait(void) {
    if (WXC_GetStateCode() != 1) {
        return;
    }
    data_0212c4dc++;
    ComRequest(5);
    data_021349c0.frames = 0;
    data_0212c5ac.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    FadeSet(0, 4);
    data_0212c75c.displayFlags |= 0x1c00;
}

// finale_demo (0x0204537c): per-frame update of the finale demo, with a button skip to the end.
ARM void finale_demo(void) {
    u8 key;
    if (CommFrameSync() == 0) {
        return;
    }
    CommUpdateJoy();
    data_021349c0.frames++;
    finaleDemoTable[data_021349c0.phase]();
    data_0212c564();
    func_020830ec();
    VGroupManager();
    key = 8;
    if (CommKeyCheck(key) != 0) {
        data_0212c4dc++;
        data_0212c5ac.resetValue = key - 9;
        PaletteFade_ClearBufferFlag();
        subTask_staffroll_cutout();
    }
    CommFrameUpdate();
}

// demo_00 (0x02045418): pans the camera down in the staff roll, then moves the demo to its next phase.
ARM void demo_00(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    if ((data_021349c0.frames & 1) == 0) {
        return;
    }
    data_02134d30.entity->animationState = 0;
    if (data_0212c648.unk_22 < 0x7b) {
        data_0212c648.unk_22 = data_0212c648.unk_22 + 1;
        data_0212c75c.unk_30 = data_0212c648.unk_22;
        data_0212c75c.unk_24 = data_0212c75c.unk_30;
    } else {
        data_021349c0.phase++;
        data_021349c0.subPhase = 0;
        data_021349c0.timer = 0x5a;
    }
}
