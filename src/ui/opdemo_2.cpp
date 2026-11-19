#include "engine/functions.h"
#include "game/scene.h"
#include "global.h"
#include "engine/irq.h"
#include "engine/message_request.h"

// scene_03 -> scene_03 (guess: intro/opening state machine of the scene block)
// fairy_talkmove -> fairy_talkmove
// opdemo_scroll -> opdemo_scroll
void scene_03(void) {
    switch (effectState.phase) {
        case 0:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer == 0) {
                effectState.phase++;
                effectState.sceneFlag = 4;
            }
            break;
        case 1:
            *(Entity **)&mapState = playerWork[0].entity;
            effectState.timer = 0x78;
            break;
        case 2:
            opdemo_scroll();
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            effectState.sceneFlag = 5;
            {
                Entity *fx = GetSetWork(0x5a, 1, 0x14);
                fx->x.HALF.HI = playerWork[0].entity->x.HALF.HI - 8;
                fx->y.HALF.HI = playerWork[0].entity->y.HALF.HI - 8;
            }
            DemoLinkWalkSet(0, 8, 8);
            playerWork[0].state = 8;
            break;
        case 3:
            opdemo_scroll();
            effectState.timer = 0xb4;
            break;
        case 4:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer == 0) {
                effectState.phase++;
            }
            break;
        case 5:
            if ((frameState.frameCount & 3) != 0) {
                return;
            }
            if (effectState.fadeStep < 0x10) {
                blendRequest.resetValue = -1;
                effectState.fadeStep++;
                return;
            }
            effectState.phase++;
            effectState.timer = 0x5a;
            Status_ArmIfEnabled();
            SoundReq(0x80040000);
            break;
        case 6: {
            u8 counter;
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            counter = data_0212c4dc;
            data_0212c4dc = counter + 1;
            effectState.phase = 0;
        }
        default:
            break;
    }
}

// Waits until the scene control block is idle, then starts effect effectId in slot.
int fairy_talkmove(u8 slot, u16 effectId) {
    u8 mode = messageRequest.phase & 0x7f;
    if (mode == 6) {
        Status_ArmIfEnabled();
    }
    mode = messageRequest.phase & 0x7f;
    if (mode == 0) {
        effectState.activeSlot = 0xff;
        effectState.timer = effectState.timer - 1;
        if (effectState.timer == 0) {
            effectState.phase++;
            effectState.timer = 0x1e;
            fairy_talkset(slot, effectId);
            return 1;
        }
    }
    return 0;
}
