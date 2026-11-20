#include "engine/functions.h"
#include "game/doorsel_exit.h"

// doorsel_exit (0x0202b470): leaves the door select screen once the fade has finished. In the two story modes
// (gameState.unk_01 5 and 6) the selection decides the next step (gameState.unk_48), otherwise it sets gameState byte 3
// from doorsel_difficultyBySelection. effectState.selection is the selection.
void doorsel_exit(void) {
    if (CommFrameSync() == 0) {
        return;
    }
    CommUpdateJoy();
    if (ZeldaFadeFlagGet() != 0) {
        ZeldaFadeFinish();
        DispReset();
        *(u16 *)0x05000000 = 0;
        data_021355a0[0] = 0;
        ObjMoveInit();
        ObjWorkPoolClear();
        func_0202809c();
        if (gameState.unk_01 != 5 && gameState.unk_01 != 6) {
            gameState.difficulty = doorsel_difficultyBySelection[effectState.selection];
        } else {
            switch (effectState.selection) {
            case 0:
                gameState.unk_48 = 0;
                break;
            case 1:
                gameState.unk_48 = 2;
                break;
            case 2:
                gameState.unk_48 = 1;
                break;
            }
        }
        Task_Chain(2);
    } else {
        CommFrameUpdate();
    }
}
