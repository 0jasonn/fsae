#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_obj_view.h"
#include "ui/widget/slider.h"

// slider: functions Slider_setPosition (0x020b9720), Slider_setPositionChecked (0x020b9740) and Slider_updateFlags
// (0x020b97d4), all matching. The slider keeps two children at +0x14 (see rect_pair.cpp for the child layout).

extern "C" void Slider_updateFlags(Slider *self);

// Slider_setPosition(self, position) (0x020b9720, provisional name): stores the position, scales it by the step and
// updates the child flags
extern "C" void Slider_setPosition(Slider *self, s16 position);
void Slider_setPosition(Slider *self, s16 position) {
    self->position = position;
    self->scaled = self->position * self->step;
    Slider_updateFlags(self);
}

// Slider_setPositionChecked(self, position) (0x020b9740, provisional name): returns 0 when the position is unchanged,
// otherwise sets it and stores the position times 0x17 in +0x3a, returning 1
extern "C" s32 Slider_setPositionChecked(Slider *self, s16 position);
s32 Slider_setPositionChecked(Slider *self, s16 position) {
    if (self->position == position) {
        return 0;
    }
    Slider_setPosition(self, position);
    self->result = self->scaled * 0x17;
    return 1;
}
