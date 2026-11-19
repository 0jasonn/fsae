#include "engine/functions.h"
#include "game/scene.h"
#include "ui/opdemo.h"
#include "ui/opdemo_api.h"
#include "global.h"
#include "engine/irq.h"
#include "engine/message_request.h"

// data_02134d30 is an array of 0x14-byte NPC slots (see GetNPC); each slot's entity pointer is at +0x0c.
#define SCENE_SLOT_ENTITY(offset) (*(Entity **)((u8 *)&data_02134d30 + (offset)))

// scene_05, 0x02052244: the fifth opening scene (fairy talk and the end of the intro).
void scene_05(void) {
    switch (effectState.phase) {
        case 0:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
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
            effectState.phase++;
            SoundReq(0x1fe);
            return;
        case 2:
            if (effectState.fadeStep < 0x10) {
                if ((frameState.frameCount & 7) == 0) {
                    effectState.fadeStep++;
                }
                return;
            }
            effectState.phase++;
            effectState.timer = 0x3c;
            return;
        case 3:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0xf0;
            bunshin_set();
            return;
        case 4:
            if (effectState.timer == 0x78) {
                SoundReq(0x208);
            }
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            SoundReq(0x1ff);
            return;
        case 5:
            if (effectState.fadeStep != 0) {
                if ((frameState.frameCount & 7) == 0) {
                    effectState.fadeStep--;
                }
                return;
            }
            effectState.phase++;
            effectState.timer = 0x78;
            SoundReq(0x1fd);
            return;
        case 6:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0x3c;
            data_02134924 |= 0x10;
            SoundReq(0x222);
            SoundReq(0x800b01b0);
            return;
        case 7:
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            effectState.phase++;
            effectState.timer = 0x1e;
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
            if ((messageRequest.phase & 0x7f) != 6) {
                return;
            }
            Status_ArmIfEnabled();
            effectState.activeSlot = 0xff;
            effectState.phase++;
            effectState.timer = 0x78;
            data_02134924 |= 0x20;
            SoundReq(0x80040000);
            return;
        case 13:
            if ((frameState.frameCount & 1) == 0) {
                return;
            }
            if (mapState.scrollY > 0x5b) {
                mapState.scrollY--;
                displayState.bg[3].scrollY = mapState.scrollY;
                displayState.bg[2].scrollY = displayState.bg[3].scrollY;
                return;
            }
            SoundReq(0x1b1);
            effectState.phase++;
            effectState.timer = 0x1a4;
            return;
        case 14:
            if (effectState.timer == 0x3c) {
                SoundReq(0x201);
                fairy_set(0, 6, 0x28);
                fairy_set(1, 7, 0x28);
                fairy_set(2, 8, 0x28);
            }
            effectState.timer = effectState.timer - 1;
            if (effectState.timer != 0) {
                return;
            }
            blendRequest.resetValue = -1;
            PaletteFade_ClearBufferFlag();
            SetCgColor(0, 0x6739);
            effectState.stepTimer = 0;
            effectState.stepIndex = 0xff;
            data_0212c500 = 2;
            data_0212c4dc = 0;
            data_0212c510 &= 0xfff7;
            return;
        default:
            return;
    }
}
