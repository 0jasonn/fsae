#include "game/scene_d.h"
#include "global.h"

// Scene_UpdateIntro -> Scene_UpdateIntro (guess: intro/opening state machine of the scene block)
// Scene_UpdateSlotWait -> Scene_UpdateSlotWait
// Scene_FollowCameraTarget -> Scene_FollowCameraTarget
ARM void Scene_UpdateIntro(void) {
    switch (data_021349c0[EFFECT_STATE_SCENE]) {
        case 0:
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) == 0) {
                data_021349c0[EFFECT_STATE_SCENE]++;
                data_021349c0[EFFECT_STATE_FLAG_E] = 4;
            }
            break;
        case 1: {
            Entity *player = data_0212ceb0[0].entity;
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0x78;
            *(Entity **)&data_0212c648 = player;
            break;
        }
        case 2:
            Scene_FollowCameraTarget();
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            data_021349c0[EFFECT_STATE_SCENE]++;
            data_021349c0[EFFECT_STATE_FLAG_E] = 5;
            {
                Entity *fx = CreateFx(0x5a, 1, 0x14);
                fx->x.HALF.HI = data_0212ceb0[0].entity->x.HALF.HI - 8;
                fx->y.HALF.HI = data_0212ceb0[0].entity->y.HALF.HI - 8;
            }
            func_020725d0(0, 8, 8);
            data_0212ceb0[0].unk_0c = 8;
            break;
        case 3:
            Scene_FollowCameraTarget();
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0xb4;
            break;
        case 4:
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) == 0) {
                data_021349c0[EFFECT_STATE_SCENE]++;
            }
            break;
        case 5:
            if ((data_0212c594 & 3) != 0) {
                return;
            }
            if (data_021349c0[EFFECT_STATE_LEVEL] < 0x10) {
                data_0212c5ac.resetValue = -1;
                data_021349c0[EFFECT_STATE_LEVEL]++;
                return;
            }
            data_021349c0[EFFECT_STATE_SCENE]++;
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0x5a;
            Status_ArmIfEnabled();
            SoundReq(0x80040000);
            break;
        case 6: {
            u8 counter;
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            counter = data_0212c4dc;
            data_0212c4dc = counter + 1;
            data_021349c0[EFFECT_STATE_SCENE] = 0;
        }
        default:
            break;
    }
}

// Waits until the scene control block is idle, then starts effect effectId in slot.
ARM int Scene_UpdateSlotWait(s32 slot, s32 effectId) {
    u8 mode = data_0217d384[SCENE_CTRL_MODE] & 0x7f;
    if (mode == 6) {
        Status_ArmIfEnabled();
    }
    mode = data_0217d384[SCENE_CTRL_MODE] & 0x7f;
    if (mode == 0) {
        data_021349c0[EFFECT_STATE_ACTIVE_SLOT] = 0xff;
        *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
        if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) == 0) {
            data_021349c0[EFFECT_STATE_SCENE]++;
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0x1e;
            Scene_StartSlotEffect(slot, effectId);
            return 1;
        }
    }
    return 0;
}
