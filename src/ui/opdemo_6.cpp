#include "engine/functions.h"
#include "game/scene.h"
#include "ui/opdemo.h"
#include "ui/opdemo_api.h"
#include "global.h"

// data_02134d30 is an array of 0x14-byte NPC slots (see GetNPC); each slot's entity pointer is at +0x0c.
#define SCENE_SLOT_ENTITY(offset) (*(Entity **)((u8 *)&data_02134d30 + (offset)))

// scene_04, 0x02051d84: the fourth opening scene (fairy and message sequence).
void scene_04(void) {
    switch (effectState[EFFECT_STATE_SCENE]) {
        case 0:
            mapState.cameraX = 0x10;
            displayState.unk_30 = 0x10;
            displayState.scrollX = 0x10;
            SoundReq(0x800b01ad);
            effectState[EFFECT_STATE_SCENE]++;
            return;
        case 1:
            if ((data_0212c594 & 0x1f) != 0) {
                return;
            }
            effectState[EFFECT_STATE_LEVEL]--;
            if (effectState[EFFECT_STATE_LEVEL] != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x78;
            SCENE_SLOT_ENTITY(0x0c) = GetSetWork(0x5a, 0, 0);
            SCENE_SLOT_ENTITY(0x20) = GetSetWork(0x5a, 0, 1);
            SCENE_SLOT_ENTITY(0x34) = GetSetWork(0x5a, 0, 2);
            SoundReq(0x201);
            return;
        case 2:
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            MessageRequest(8);
            messageRequest[SCENE_CTRL_SUBMODE_3] = (messageRequest[SCENE_CTRL_SUBMODE_3] & ~0x1f) | 1;
            messageRequest[SCENE_CTRL_SUBMODE_4] = (messageRequest[SCENE_CTRL_SUBMODE_4] & ~0x1f) | 0x10;
            effectState[EFFECT_STATE_SCENE]++;
            return;
        case 3:
            if ((data_0212c594 & 1) == 0) {
                return;
            }
            mapState.cameraX++;
            displayState.unk_30 = mapState.cameraX;
            displayState.scrollX = displayState.unk_30;
            if (mapState.cameraX < 0x88) {
                return;
            }
            MessageRequest(9);
            messageRequest[SCENE_CTRL_SUBMODE_3] = (messageRequest[SCENE_CTRL_SUBMODE_3] & ~0x1f) | 1;
            messageRequest[SCENE_CTRL_SUBMODE_4] = (messageRequest[SCENE_CTRL_SUBMODE_4] & ~0x1f) | 0x10;
            effectState[EFFECT_STATE_SCENE]++;
            return;
        case 4:
            if ((data_0212c594 & 1) == 0) {
                return;
            }
            mapState.cameraX++;
            displayState.unk_30 = mapState.cameraX;
            displayState.scrollX = displayState.unk_30;
            if (mapState.cameraX < 0xa0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x1e;
            fairy_set(1, 0, 0x78);
            return;
        case 5:
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x1e;
            fairy_set(0, 1, 0x78);
            return;
        case 6:
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0xb4;
            fairy_set(2, 2, 0x78);
            return;
        case 7:
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) == 0x3c) {
                Status_ArmIfEnabled();
            }
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x3c;
            playerWork[0].state = 0xa;
            return;
        case 8:
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) == 0x1e) {
                playerWork[0].entity->animationState = 0;
            }
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
            if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE]++;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x1e;
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
            if ((messageRequest[SCENE_CTRL_MODE] & 0x7f) != 6) {
                return;
            }
            Status_ArmIfEnabled();
            effectState[OPSCENE_ACTIVE_SLOT] = 0xff;
            playerWork[0].state = 0xb;
            fairy_set(0, 3, 0x3c);
            fairy_set(1, 4, 0x3c);
            fairy_set(2, 5, 0x3c);
            SoundReq(0x201);
            effectState[EFFECT_STATE_SCENE]++;
            return;
        case 13:
            opdemo_scroll();
            if ((data_02134924 & 4) == 0) {
                return;
            }
            effectState[EFFECT_STATE_SCENE] = 0;
            *(u16 *)(effectState + EFFECT_STATE_TIMER) = 0x78;
            data_0212c4dc++;
            return;
        default:
            return;
    }
}

