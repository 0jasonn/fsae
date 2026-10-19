#include "game/scene_d.h"
#include "global.h"

// Scene_FinishStartup -> Scene_FinishStartup
// Scene_NoOp -> Scene_NoOp
// Scene_ReleaseResources -> Scene_ReleaseResources
// Scene_UpdatePlayerInput -> Scene_UpdatePlayerInput
ARM void Scene_FinishStartup(void) {
    *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
    if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) != 0) {
        return;
    }
    data_0212c75c.displayFlags = 0x1f40;
    GX_DispOn();
    data_0212c5ac.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    func_0204625c(2, 8);
    data_0212c4dc++;
}

ARM void Scene_NoOp(void) {
}

ARM void Scene_ReleaseResources(void) {
    func_020909c8();
    func_0208da4c();
}
