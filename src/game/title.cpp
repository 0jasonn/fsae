#include "engine/functions.h"
#include "game/scene_d.h"
#include "global.h"

// title_wait -> title_wait
// Scene_NoOp -> Scene_NoOp
// title_move -> title_move
// title_machiuke_joy -> title_machiuke_joy
ARM void title_wait(void) {
    *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) = *(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) - 1;
    if (*(u16 *)(data_021349c0 + EFFECT_STATE_TIMER) != 0) {
        return;
    }
    data_0212c75c.displayFlags = 0x1f40;
    GX_DispOn();
    data_0212c5ac.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    FadeSet(2, 8);
    data_0212c4dc++;
}

ARM void Scene_NoOp(void) {
}

ARM void title_move(void) {
    func_020909c8();
    KnifeApp_getInstance();
}
