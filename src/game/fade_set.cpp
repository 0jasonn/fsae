#include "engine/functions.h"
#include "actor/enemy/ending.h"

// FadeSet (0x0204625c): starts a palette fade with the given mode and step.
void FadeSet(u8 mode, u8 step) {
    BlendRequest *fade = &blendRequest;
    u8 color;

    fade->blendMode = mode;
    fade->blendStep = step;
    fade->blendEnabled = 1;
    fade->unk_02 = 0;
    if (mode > 3) {
        fade->blendWeight = 0x100 - fade->blendWeight;
    } else {
        fade->blendWeight = 0x100;
    }
    if (fade->fadeRunning == 0) {
        return;
    }
    color = 0;
    if (mode >= 2) {
        color = 0x19;
    }
    blendRequest.blendColor = color;
    em2f_mapFlag = 0;
}
