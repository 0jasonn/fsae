#include "actor/object/ranking5.h"
#include "engine/functions.h"
#include "engine/misc.h"
#include "engine/effect_state.h"
#include "game/rankingsave.h"
#include "engine/vgroup.h"
#include "engine/blend_request.h"
#include "engine/display_state.h"
#include "engine/map_state.h"
#include "engine/frame_counter.h"
#include "engine/vblank_request.h"
#include "engine/misc.h"

// ranking_hyosyo() (0x02055b20): result presentation of the ranking scene: builds the player table and the layers, shows the
// scores for a while, fades out and then either returns to the stage select or chains the next task.
void ranking_hyosyo(void) {
    u8 step = data_0212c4dc;
    u8 zero = 0;

    switch (step) {
    case 0:
        if (blendRequest.blendEnabled != 0) {
            return;
        }
        make_hyosyo();
        effectState.removeFlag = 1;
        displayState.displayFlags = 0x1c40;
        displayState.bg[2].scrollX = 0;
        displayState.bg[2].scrollY = 0x130;
        displayState.bg[3].scrollX = 0;
        displayState.bg[3].scrollY = 0x130;
        mapState.scrollX = 0;
        mapState.scrollY = 0x130;
        data_0212c4dc++;
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
            frameCounter.timer = (gameState.active != 0 || gameState.score == 0) ? 0x12c : 0x294;
        } else {
            frameCounter.timer = 0xb4;
        }
        FadeSet(0, 4);
        break;
    case 1:
        if (blendRequest.blendEnabled != 0) {
            return;
        }
        data_0212c4dc = step + 1;
        break;
    case 2:
        frameCounter.timer--;
        if (frameCounter.timer == 0) {
            data_0212c4dc = step + 1;
            SoundReq(0x80040000);
            FadeSet(1, 8);
        }
        break;
    case 3:
        if (blendRequest.blendEnabled != 0) {
            return;
        }
        SoundReq(0x80010000);
        ObjWorkPoolClear();
        ObjMoveInit();
        VGroupInit();
        DispReset();
        *(u16 *)0x05000000 = zero;
        data_021355a0 = zero;
        MIi_CpuClearFast(zero, (void *)0x06000000, 0x20000);
        if (gameState.active != 0) {
            Task_Chain(2);
            data_0212c500 = 1;
            gameState.phaseFlags = 0x28;
            GameState_UpdatePhase();
        } else {
            data_0212c4dc = zero;
            data_0212c500++;
        }
        break;
    }
    data_0212c564();
    func_020830ec();
}
