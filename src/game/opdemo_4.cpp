#include "engine/functions.h"
#include "engine/misc_d.h"
#include "game/opdemo_c.h"
#include "global.h"

// op_scene_01 (symbol op_scene_01, original scene_01()): the first opening scene. The step index is
// data_021349c0[EFFECT_STATE_SCENE] and the countdown is the u16 at EFFECT_STATE_TIMER.
extern "C" void op_scene_01(void);

ARM void op_scene_01(void) {
    switch (data_021349c0[EFFECT_STATE_SCENE]) {
        case 0:
            if ((data_0212c594 & 0x1f) != 0) {
                return;
            }
            if (data_021349c0[EFFECT_STATE_LEVEL] < 7) {
                data_021349c0[EFFECT_STATE_LEVEL]++;
                return;
            }
            data_021349c0[EFFECT_STATE_SCENE]++;
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0x78;
            SoundReq(0x203);
            return;
        case 1:
            if ((data_0212c594 & 0xf) == 0) {
                data_02134d30.entity->animationState = (u8)((Random() & 3) << 1);
                data_0212ceb0[0].entity->animationState = (u8)((Random() & 3) << 1);
            }
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) == 0) {
                Entity *spawned;
                data_021349c0[EFFECT_STATE_SCENE]++;
                SoundReq(0x1ae);
                spawned = GetSetWork(0x62, 0, 0);
                spawned->x.HALF.HI = 0xa0;
                spawned->y.HALF.HI = 4;
            }
            return;
        case 2:
            if (data_02134d30.entity != NULL && (data_0212c594 & 0xf) == 0) {
                data_02134d30.entity->animationState = (u8)((Random() & 3) << 1);
                data_0212ceb0[0].entity->animationState = (u8)((Random() & 3) << 1);
            }
            if (data_021349c0[OPSCENE_SUBSTATE] == 1) {
                PutNPC(0);
                data_021349c0[OPSCENE_SUBSTATE] = 0;
                return;
            }
            if (data_021349c0[OPSCENE_SUBSTATE] != 2) {
                return;
            }
            {
                Entity *spawned = GetSetWork(0x5a, 1, 0x14);
                spawned->x.HALF.HI = data_0212ceb0[0].entity->x.HALF.HI - 8;
                spawned->y.HALF.HI = data_0212ceb0[0].entity->y.HALF.HI - 0x10;
            }
            data_021349c0[EFFECT_STATE_SCENE]++;
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0x3c;
            DemoLinkWalkSet(0, 0x10, 0x10);
            data_0212ceb0[0].entity->animationState = 0;
            return;
        case 3:
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) == 0) {
                data_021349c0[EFFECT_STATE_SCENE]++;
            }
            return;
        case 4:
            if (data_0212c648.cameraX > 0x10) {
                data_0212c648.cameraX -= 8;
                data_0212c75c.unk_30 = data_0212c648.cameraX;
                data_0212c75c.scrollX = data_0212c75c.unk_30;
                return;
            }
            data_0212c648.cameraX = 0x10;
            data_0212c75c.unk_30 = 0x10;
            data_021349c0[EFFECT_STATE_SCENE]++;
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0x28;
            data_0212c75c.scrollX = 0x10;
            SoundReq(0x1af);
            return;
        case 5:
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) == 0) {
                gufu_flash();
            }
            return;
        case 6:
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) == 0) {
                gufu_flash();
            }
            return;
        case 7:
            *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) == 0) {
                gufu_flash();
            }
            return;
        case 8:
            if (data_0212c5ac.blendEnabled != 0) {
                return;
            }
            data_0212c5ac.blendColor = 0;
            data_0212c5ac.resetValue = 0x20fff0;
            PaletteFade_ClearBufferFlag();
            if ((data_0212c594 & 7) != 0) {
                return;
            }
            if (data_021349c0[EFFECT_STATE_LEVEL] < 7) {
                data_021349c0[EFFECT_STATE_LEVEL]++;
                return;
            }
            data_021349c0[EFFECT_STATE_SCENE]++;
            MessageRequest(4);
            messageRequest[SCENE_CTRL_SUBMODE_3] = (messageRequest[SCENE_CTRL_SUBMODE_3] & ~0x1f) | 1;
            messageRequest[SCENE_CTRL_SUBMODE_4] = (messageRequest[SCENE_CTRL_SUBMODE_4] & ~0x1f) | 0x10;
            return;
        case 9:
            if ((messageRequest[SCENE_CTRL_MODE] & 0x7f) != 6) {
                return;
            }
            Status_ArmIfEnabled();
            data_021349c0[EFFECT_STATE_SCENE]++;
            data_021349c0[EFFECT_STATE_FLAG_E] = 1;
            SoundReq(0x1fa);
            return;
        case 10:
            opdemo_scroll();
            return;
        case 11:
            if ((data_0212c594 & 1) == 0) {
                return;
            }
            if (data_0212c648.cameraX < 0x88) {
                data_0212c648.cameraX++;
                data_0212c75c.unk_30 = data_0212c648.cameraX;
                data_0212c75c.scrollX = data_0212c75c.unk_30;
            } else {
                data_0212c648.cameraX = 0x88;
                data_0212c4dc++;
                data_021349c0[EFFECT_STATE_SCENE] = 4;
                *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = 0x28;
            }
            return;
        default:
            return;
    }
}
