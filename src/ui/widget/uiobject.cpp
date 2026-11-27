#include "engine/functions.h"
#include "global.h"
#include "ui/widget/uiobject.h"

// Functions in this file (original names from the debug build):
//   calc_liner (0x020acab4), calc_easeIn (0x020acb04), calc_easeOut (0x020acb7c)
// They return the interpolated pair by value (ABI: the hidden result pointer is the first argument, the same as
// UIObjectCalcFunc in ui/widget/uiobject.h).

extern const s16 data_020c91fc[][2]; // easing table: the first value of each row is used by the ease curves

// Linear interpolation of from and to by ratio (0x1000 is the end)
UIPos2 calc_liner(const s32 *from, const s32 *to, s32 ratio) {
    UIPos2 result;
    s32 weight = ratio >> 3;
    s32 toX = to[0];
    s32 toY = to[1];

    result.x = (from[0] * (0x200 - weight) + toX * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + toY * weight) >> 9;
    return result;
}

// Ease-in curve: the ratio is pulled back by the table value, then interpolated as in calc_liner
UIPos2 calc_easeIn(const s32 *from, const s32 *to, s32 ratio) {
    UIPos2 result;
    s32 weight;

    weight = ratio + (((s16)data_020c91fc[(ratio << 3) >> 4][0] * (s16)-0x517) >> 12);
    weight >>= 3;
    result.x = (from[0] * (0x200 - weight) + to[0] * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + to[1] * weight) >> 9;
    return result;
}

// Ease-out curve: the same as calc_easeIn with the table value added
UIPos2 calc_easeOut(const s32 *from, const s32 *to, s32 ratio) {
    UIPos2 result;
    s32 weight;

    weight = ratio + (((s16)data_020c91fc[(ratio << 3) >> 4][0] * (s16)0x517) >> 12);
    weight >>= 3;
    result.x = (from[0] * (0x200 - weight) + to[0] * weight) >> 9;
    result.y = (from[1] * (0x200 - weight) + to[1] * weight) >> 9;
    return result;
}

// Functions in this file (original names from the debug build):
//   UIObject::init(unsigned char) (0x020acbf4), UIObject::update() (0x020acc2c), UIObject::updateTime(long) (0x020acc7c)

extern "C" void ResPlayer_AdvanceAndRefresh(void *anim, s32 c); // animation step, the same as game/subtask.h

// UIObject::init(unsigned char) (0x020acbf4): clears the object, stores the kind, sets the active flags, liner curve
void UIObject_init(UIObject *self, u8 kind) {
    MI_CpuFill8(self, 0, sizeof(UIObject));
    self->kind = kind;
    self->unk_02[1] = 1;
    self->calcFunc = calc_liner;
    self->active = 1;
}

// UIObject::update() (0x020acc2c): advances the move, the frame counter (wraps after 0x77) and the attached animation
extern "C" void UIObject_update(UIObject *self);
void UIObject_update(UIObject *self) {
    if (self->durationFP != 0) {
        UIObject_updateMovePos(self, 0x1000);
    }
    ++self->frameCounter;
    if (self->frameCounter > 0x77) {
        self->frameCounter = 0;
    }
    if (self->unk_54 == NULL) {
        return;
    }
    ResPlayer_AdvanceAndRefresh(self->unk_54, self->unk_50);
}

// UIObject::updateTime(long) (0x020acc7c): adds step to the elapsed time, returns TRUE once the duration is reached
BOOL UIObject_updateTime(UIObject *self, s32 step) {
    self->elapsed += step;
    if (self->elapsed >= self->durationFP) {
        self->elapsed = self->durationFP;
        return TRUE;
    }
    return FALSE;
}

// Functions in this file (original names from the debug build):
//   UIObject::movePos (0x020acca0)

// UIObject::movePos (0x020acca0): starts a move from the current position to (x, y) over duration frames
void UIObject_movePos(UIObject *self, s32 x, s32 y, s32 duration, AnimationCurve curve) {
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
