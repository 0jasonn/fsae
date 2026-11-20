#include "engine/functions.h"
#include "game/scene.h"
#include "ui/opdemo.h"
#include "global.h"
#include "engine/irq.h"
#include "engine/message_request.h"

// scene_04, 0x02051d84: the fourth opening scene (fairy and message sequence).
void scene_04(void) {
    switch (effectState.phase) {
        case 0:
            mapState.scrollY = 0x10;
            displayState.bg[3].scrollY = 0x10;
            displayState.bg[2].scrollY = 0x10;
            SoundReq(0x800b01ad);
            effectState.phase++;
            return;
        case 1:
            if ((frameState.frameCount & 0x1f) != 0) {
                return;
            }
            effectState.fadeStep--;
            if (effectState.fadeStep != 0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0x78;
            data_02134d30[0].entity = GetSetWork(0x5a, 0, 0);
            data_02134d30[1].entity = GetSetWork(0x5a, 0, 1);
            data_02134d30[2].entity = GetSetWork(0x5a, 0, 2);
            SoundReq(0x201);
            return;
        case 2:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            MessageRequest(8);
            messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
            messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
            effectState.phase++;
            return;
        case 3:
            if ((frameState.frameCount & 1) == 0) {
                return;
            }
            mapState.scrollY++;
            displayState.bg[3].scrollY = mapState.scrollY;
            displayState.bg[2].scrollY = displayState.bg[3].scrollY;
            if (mapState.scrollY < 0x88) {
                return;
            }
            MessageRequest(9);
            messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
            messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
            effectState.phase++;
            return;
        case 4:
            if ((frameState.frameCount & 1) == 0) {
                return;
            }
            mapState.scrollY++;
            displayState.bg[3].scrollY = mapState.scrollY;
            displayState.bg[2].scrollY = displayState.bg[3].scrollY;
            if (mapState.scrollY < 0xa0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0x1e;
            fairy_set(1, 0, 0x78);
            return;
        case 5:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0x1e;
            fairy_set(0, 1, 0x78);
            return;
        case 6:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0xb4;
            fairy_set(2, 2, 0x78);
            return;
        case 7:
            if (effectState.timer == 0x3c) {
                Status_ArmIfEnabled();
            }
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0x3c;
            playerWork[0].state = 0xa;
            return;
        case 8:
            if (effectState.timer == 0x1e) {
                playerWork[0].entity->animationState = 0;
            }
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0x1e;
            fairy_talkset(0, 0xa);
            return;
        case 9:
            fairy_talkmove(1, 0xb);
            return;
        case 10:
            fairy_talkmove(2, 0xc);
            return;
        case 11:
            fairy_talkmove(0, 0xd);
            return;
        case 12:
            if ((messageRequest.phase & 0x7f) != 6) {
                return;
            }
            Status_ArmIfEnabled();
            effectState.activeSlot = 0xff;
            playerWork[0].state = 0xb;
            fairy_set(0, 3, 0x3c);
            fairy_set(1, 4, 0x3c);
            fairy_set(2, 5, 0x3c);
            SoundReq(0x201);
            effectState.phase++;
            return;
        case 13:
            opdemo_scroll();
            if ((data_02134924 & 4) == 0) {
                return;
            }
            effectState.phase = 0;
            effectState.timer = 0x78;
            data_0212c4dc++;
            return;
        default:
            return;
    }
}

