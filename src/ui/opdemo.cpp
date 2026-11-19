#include "engine/functions.h"
#include "engine/misc.h"
#include "ui/opdemo.h"
#include "global.h"
#include "ui/opdemo_api.h"
#include "engine/irq.h"
#include "engine/message_request.h"

// op_scene_01 (symbol op_scene_01, original scene_01()): the first opening scene. The step index is
// effectState.phase and the countdown is effectState.timer.

void op_scene_01(void) {
    switch (effectState.phase) {
        case 0:
            if ((frameState.frameCount & 0x1f) != 0) {
                return;
            }
            if (effectState.fadeStep < 7) {
                effectState.fadeStep++;
                return;
            }
            effectState.phase++;
            effectState.timer = 0x78;
            SoundReq(0x203);
            return;
        case 1:
            if ((frameState.frameCount & 0xf) == 0) {
                data_02134d30.entity->animationState = (u8)((Random() & 3) << 1);
                playerWork[0].entity->animationState = (u8)((Random() & 3) << 1);
            }
            effectState.timer = effectState.timer - 1;
            if (effectState.timer == 0) {
                Entity *spawned;
                effectState.phase++;
                SoundReq(0x1ae);
                spawned = GetSetWork(0x62, 0, 0);
                spawned->x.HALF.HI = 0xa0;
                spawned->y.HALF.HI = 4;
            }
            return;
        case 2:
            if (data_02134d30.entity != NULL && (frameState.frameCount & 0xf) == 0) {
                data_02134d30.entity->animationState = (u8)((Random() & 3) << 1);
                playerWork[0].entity->animationState = (u8)((Random() & 3) << 1);
            }
            if (effectState.subState == 1) {
                PutNPC(0);
                effectState.subState = 0;
                return;
            }
            if (effectState.subState != 2) {
                return;
            }
            {
                Entity *spawned = GetSetWork(0x5a, 1, 0x14);
                spawned->x.HALF.HI = playerWork[0].entity->x.HALF.HI - 8;
                spawned->y.HALF.HI = playerWork[0].entity->y.HALF.HI - 0x10;
            }
            effectState.phase++;
            effectState.timer = 0x3c;
            DemoLinkWalkSet(0, 0x10, 0x10);
            playerWork[0].entity->animationState = 0;
            return;
        case 3:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer == 0) {
                effectState.phase++;
            }
            return;
        case 4:
            if (mapState.scrollY > 0x10) {
                mapState.scrollY -= 8;
                displayState.bg[3].scrollY = mapState.scrollY;
                displayState.bg[2].scrollY = displayState.bg[3].scrollY;
                return;
            }
            mapState.scrollY = 0x10;
            displayState.bg[3].scrollY = 0x10;
            effectState.phase++;
            effectState.timer = 0x28;
            displayState.bg[2].scrollY = 0x10;
            SoundReq(0x1af);
            return;
        case 5:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer == 0) {
                gufu_flash();
            }
            return;
        case 6:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer == 0) {
                gufu_flash();
            }
            return;
        case 7:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer == 0) {
                gufu_flash();
            }
            return;
        case 8:
            if (blendRequest.blendEnabled != 0) {
                return;
            }
            blendRequest.blendColor = 0;
            blendRequest.resetValue = 0x20fff0;
            PaletteFade_ClearBufferFlag();
            if ((frameState.frameCount & 7) != 0) {
                return;
            }
            if (effectState.fadeStep < 7) {
                effectState.fadeStep++;
                return;
            }
            effectState.phase++;
            MessageRequest(4);
            messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
            messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
            return;
        case 9:
            if ((messageRequest.phase & 0x7f) != 6) {
                return;
            }
            Status_ArmIfEnabled();
            effectState.phase++;
            effectState.sceneFlag = 1;
            SoundReq(0x1fa);
            return;
        case 10:
            opdemo_scroll();
            return;
        case 11:
            if ((frameState.frameCount & 1) == 0) {
                return;
            }
            if (mapState.scrollY < 0x88) {
                mapState.scrollY++;
                displayState.bg[3].scrollY = mapState.scrollY;
                displayState.bg[2].scrollY = displayState.bg[3].scrollY;
            } else {
                mapState.scrollY = 0x88;
                data_0212c4dc++;
                effectState.phase = 4;
                effectState.timer = 0x28;
            }
            return;
        default:
            return;
    }
}

void gufu_flash(void) {
    effectState.timer = 0x14;
    effectState.phase++;
    effectState.fadeStep = 0;
    blendRequest.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    FadeSet(2, 8);
    SoundReq(0x1f9);
}
