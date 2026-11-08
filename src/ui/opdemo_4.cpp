#include "engine/functions.h"
#include "game/scene.h"
#include "ui/opdemo.h"
#include "ui/opdemo_api.h"
#include "global.h"

// data_02134d30 is an array of 0x14-byte NPC slots (see GetNPC); each slot's entity pointer is at +0x0c.
#define SCENE_SLOT_ENTITY(offset) (*(Entity **)((u8 *)&data_02134d30 + (offset)))

// scene_05, 0x02052244: the fifth opening scene (fairy talk and the end of the intro).
void scene_05(void) {
    switch (effectState[EFFECT_STATE_SCENE]) {
        case 0:
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            func_02072554(1);
            func_02072554(2);
            func_02072554(3);
            playerWork[1].state = 0xb;
            playerWork[2].state = 0xb;
            playerWork[3].state = 0xb;
            return;
        case 1:
            blendRequest.resetValue = 0xf877ffff;
            blendRequest.blendColor = 0x1c;
            effectState[EFFECT_STATE_SCENE]++;
            SoundReq(0x1fe);
            return;
        case 2:
            if (effectState[EFFECT_STATE_LEVEL] < 0x10) {
                if ((data_0212c594 & 7) == 0) {
                    effectState[EFFECT_STATE_LEVEL]++;
                }
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x3c;
            return;
        case 3:
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0xf0;
            bunshin_set();
            return;
        case 4:
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) == 0x78) {
                SoundReq(0x208);
            }
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            SoundReq(0x1ff);
            return;
        case 5:
            if (effectState[EFFECT_STATE_LEVEL] != 0) {
                if ((data_0212c594 & 7) == 0) {
                    effectState[EFFECT_STATE_LEVEL]--;
                }
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x78;
            SoundReq(0x1fd);
            return;
        case 6:
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x3c;
            data_02134924 |= 0x10;
            SoundReq(0x222);
            SoundReq(0x800b01b0);
            return;
        case 7:
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x1e;
            fairy_talkset(0, 0xe);
            return;
        case 8:
            fairy_talkmove(1, 0xf);
            return;
        case 9:
            fairy_talkmove(2, 0x10);
            return;
        case 10:
            fairy_talkmove(0, 0x11);
            return;
        case 11:
            fairy_talkmove(1, 0x12);
            return;
        case 12:
            if ((messageRequest[SCENE_CTRL_MODE] & 0x7f) != 6) {
                return;
            }
            Status_ArmIfEnabled();
            effectState[OPSCENE_ACTIVE_SLOT] = 0xff;
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x78;
            data_02134924 |= 0x20;
            SoundReq(0x80040000);
            return;
        case 13:
            if ((data_0212c594 & 1) == 0) {
                return;
            }
            if (mapState.cameraX > 0x5b) {
                mapState.cameraX--;
                displayState.unk_30 = mapState.cameraX;
                displayState.scrollX = displayState.unk_30;
                return;
            }
            SoundReq(0x1b1);
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x1a4;
            return;
        case 14:
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) == 0x3c) {
                SoundReq(0x201);
                fairy_set(0, 6, 0x28);
                fairy_set(1, 7, 0x28);
                fairy_set(2, 8, 0x28);
            }
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            blendRequest.resetValue = -1;
            PaletteFade_ClearBufferFlag();
            SetCgColor(0, 0x6739);
            effectState[EFFECT_STATE_STEP_TIMER] = 0;
            effectState[EFFECT_STATE_STEP_INDEX] = 0xff;
            data_0212c500 = 2;
            data_0212c4dc = 0;
            data_0212c510 &= 0xfff7;
            return;
        default:
            return;
    }
}
