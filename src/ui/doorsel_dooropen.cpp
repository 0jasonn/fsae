#include "engine/functions.h"
#include "engine/player.h"
#include "engine/effect_state.h"
#include "engine/data_0212c500.h"
#include "knife/comm/commframe_sync.h"
#include "knife/comm/commupdatejoy.h"
#include "game/keyclear_api.h"

// doorsel_dooropen(), 0x0202b18c: the door opening sequence after the selection. data_0212c4dc is the step (0..7),
// effectState holds the timer and the animation bytes (progress, stepTimer, stepIndex). The A button skips the
// waiting steps 2..4. Step 3 goes through the state pointer: its byte stores make mwcc reload data_0212c4dc there,
// as in the ROM, while the other steps use effectState directly (their constants are stored one at a time).
void doorsel_dooropen(void) {
    EffectState *state = &effectState;
    u8 i;

    if (CommFrameSync() == 0) {
        return;
    }
    CommUpdateJoy();
    if ((playerKeys[0] & 1) && data_0212c4dc >= 2 && data_0212c4dc <= 4) {
        data_0212c4dc = 4;
        effectState.timer = 1;
    }
    switch (data_0212c4dc) {
    case 0:
        SoundReq(0x3e);
        effectState.timer = 0x1e;
        if (gameState.unk_01 != 5 && gameState.unk_01 != 6) {
            data_0212c4dc = data_0212c4dc + 1;
        } else {
            effectState.progress = 2;
            effectState.timer = 0x28;
            data_0212c4dc = 5;
        }
        break;
    case 1:
        effectState.timer = effectState.timer - 1;
        if (effectState.timer == 0) {
            data_0212c4dc = data_0212c4dc + 1;
            SoundReq(0xf);
            for (i = 0; i < gameState.playerCount; i++) {
                playerWork[i].state = 4;
                playerWork[i].stateTimer = 0xff;
            }
            effectState.stepTimer = 0x20;
            GetSetWork(0x31, 0xb, 0);
            GetSetWork(0x31, 0xb, 1);
            GetSetWork(0x31, 0xb, 2);
            effectState.timer = 0xb4;
        }
        break;
    case 2:
        effectState.timer = effectState.timer - 1;
        if (effectState.timer == 0) {
            data_0212c4dc = data_0212c4dc + 1;
            effectState.stepIndex = 4;
        }
        break;
    case 3:
        state->stepTimer -= 1;
        if (state->stepTimer < 0x18) {
            effectState.stepIndex = 8;
        }
        if (state->stepTimer < 8) {
            effectState.stepIndex = 0xc;
            state->timer = 0x78;
            data_0212c4dc = data_0212c4dc + 1;
        }
        break;
    case 4:
        effectState.timer = effectState.timer - 1;
        if (effectState.timer == 0) {
            data_0212c4dc = data_0212c4dc + 1;
            CgLoad(0x23);
            GetSetWork(0x31, (u8)(effectState.selection + 5), 0);
            effectState.progress = 2;
            effectState.timer = 0x28;
        }
        break;
    case 5:
        effectState.timer = effectState.timer - 1;
        if (effectState.timer == 0) {
            data_0212c4dc = data_0212c4dc + 1;
            effectState.progress = 3;
        }
        break;
    case 6:
        if (effectState.progress == 4) {
            data_0212c4dc = data_0212c4dc + 1;
            effectState.timer = 0x3c;
        }
        break;
    case 7:
        effectState.timer = effectState.timer - 1;
        if (effectState.timer == 0) {
            data_0212c500 = data_0212c500 + 1;
            data_0212c4dc = 0;
            effectState.progress = 5;
            keyClear();
            return;
        }
        break;
    }
    CommFrameUpdate();
}
