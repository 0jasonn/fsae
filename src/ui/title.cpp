#include "engine/functions.h"
#include "game/scene.h"
#include "global.h"

// title_wait -> title_wait
// Scene_NoOp -> Scene_NoOp
// title_move -> title_move
// title_machiuke_joy -> title_machiuke_joy
void title_wait(void) {
    *(u16 *)(effectState + EFFECT_STATE_TIMER) = *(u16 *)(effectState + EFFECT_STATE_TIMER) - 1;
    if (*(u16 *)(effectState + EFFECT_STATE_TIMER) != 0) {
        return;
    }
    displayState.displayFlags = 0x1f40;
    GX_DispOn();
    blendRequest.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    FadeSet(2, 8);
    data_0212c4dc++;
}

void Scene_NoOp(void) {
}

void title_move(void) {
    func_020909c8();
    KnifeApp_getInstance();
}
