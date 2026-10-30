#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"

// Functions in this file (original names from the debug build):
//   UIObject::init(unsigned char) (0x020acbf4), UIObject::update() (0x020acc2c), UIObject::updateTime(long) (0x020acc7c)

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void ResPlayer_AdvanceAndRefresh(void *anim, s32 c); // animation step, the same as game/subtask.h

// UIObject::init(unsigned char) (0x020acbf4): clears the object, stores the kind, sets the active flags, liner curve
extern "C" void UIObject_init(UIObject *self, u8 kind);
ARM void UIObject_init(UIObject *self, u8 kind) {
    MI_CpuFill8(self, 0, sizeof(UIObject));
    self->kind = kind;
    self->unk_02[1] = 1;
    self->calcFunc = calc_liner;
    self->active = 1;
}

// UIObject::update() (0x020acc2c): advances the move, the frame counter (wraps after 0x77) and the attached animation
extern "C" void UIObject_update(UIObject *self);
ARM void UIObject_update(UIObject *self) {
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
ARM BOOL UIObject_updateTime(UIObject *self, s32 step) {
    self->elapsed += step;
    if (self->elapsed >= self->durationFP) {
        self->elapsed = self->durationFP;
        return TRUE;
    }
    return FALSE;
}
