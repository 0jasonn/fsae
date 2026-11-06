#include "engine/functions.h"
#include "actor/enemy/ending.h"
#include "global.h"

// Implementer B, round 6: finale_wait (0x02045308), finale_demo (0x0204537c).

// finale_wait (0x02045308): waits for the link state, then starts the staff roll fade.
void finale_wait(void) {
    if (WXC_GetStateCode() != 1) {
        return;
    }
    data_0212c4dc++;
    ComRequest(5);
    effectState.frames = 0;
    blendRequest.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    FadeSet(0, 4);
    displayState.displayFlags |= 0x1c00;
}

// finale_demo (0x0204537c): per-frame update of the finale demo, with a button skip to the end.
void finale_demo(void) {
    u8 key;
    if (CommFrameSync() == 0) {
        return;
    }
    CommUpdateJoy();
    effectState.frames++;
    finaleDemoTable[effectState.phase]();
    data_0212c564();
    func_020830ec();
    VGroupManager();
    key = 8;
    if (CommKeyCheck(key) != 0) {
        data_0212c4dc++;
        blendRequest.resetValue = key - 9;
        PaletteFade_ClearBufferFlag();
        subTask_staffroll_cutout();
    }
    CommFrameUpdate();
}

// demo_00 (0x02045418): pans the camera down in the staff roll, then moves the demo to its next phase.
void demo_00(void) {
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    if ((effectState.frames & 1) == 0) {
        return;
    }
    data_02134d30.entity->animationState = 0;
    if (mapState.unk_22 < 0x7b) {
        mapState.unk_22 = mapState.unk_22 + 1;
        displayState.unk_30 = mapState.unk_22;
        displayState.unk_24 = displayState.unk_30;
    } else {
        effectState.phase++;
        effectState.subPhase = 0;
        effectState.timer = 0x5a;
    }
}
