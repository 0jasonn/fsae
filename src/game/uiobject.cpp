#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"

// Functions in this file (original names from the debug build):
//   UIObject::movePos (0x020acca0)
// UIObject::updateMovePos (0x020acd1c) is parked in scratch/agentF/nonmatching/UIObject_updateMovePos.cpp

// UIObject::movePos (0x020acca0): starts a move from the current position to (x, y) over duration frames
ARM void UIObject_movePos(UIObject *self, s32 x, s32 y, s32 duration, AnimationCurve curve) {
    self->fromX = self->pos.x;
    self->fromY = self->pos.y;
    self->toX = x;
    self->toY = y;
    self->durationFP = duration << 12;
    self->elapsed = 0;
    switch (curve) {
    case ANIMATION_CURVE_LINER:
        self->calcFunc = calc_liner;
        break;
    case ANIMATION_CURVE_EASE_IN:
        self->calcFunc = calc_easeIn;
        break;
    case ANIMATION_CURVE_EASE_OUT:
        self->calcFunc = calc_easeOut;
        break;
    case ANIMATION_CURVE_NONE:
        break;
    }
}
