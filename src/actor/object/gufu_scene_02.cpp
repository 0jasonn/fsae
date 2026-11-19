#include "engine/functions.h"
#include "engine/effect_state.h"
#include "engine/message_request.h"
#include "engine/misc.h"

// gufu_scene_02 (0x02051994): opening scene 2 (the Gufu / fairy dialog): waits, asks for the two messages, arms the
// status display and fades out into the next scene.
void gufu_scene_02(void) {
    switch (effectState.phase) {
    case 4:
        effectState.timer--;
        if (effectState.timer != 0) {
            return;
        }
        MessageRequest(5);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
        effectState.phase++;
        return;
    case 5:
        if ((messageRequest.phase & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        effectState.phase++;
        effectState.timer = 0x3c;
        effectState.sceneFlag = 2;
        return;
    case 6:
        effectState.timer--;
        if (effectState.timer != 0) {
            return;
        }
        MessageRequest(6);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
        effectState.phase++;
        return;
    case 7:
        if ((messageRequest.phase & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        effectState.sceneFlag = 3;
        effectState.phase++;
        SoundReq(0x203);
        return;
    case 8:
        if (effectState.sceneFlag != 0) {
            return;
        }
        effectState.phase = 0;
        data_0212c4dc++;
        effectState.timer = 0x1e;
        return;
    }
}
