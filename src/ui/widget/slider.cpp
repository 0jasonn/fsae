#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_obj_view.h"
#include "ui/widget/slider.h"
#include "ui/widget/slider_index_api.h"

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

// Provisional name. Set the selected item's row flag while it lies in the visible window.
void SliderRing_setSelectedChild(void *selfv, s32 selected) {
    Slider *self = (Slider *)selfv;
    s32 firstIndex;
    s32 slot;

    if (self->selectedIndex == -1 || self->unk_3c == 0) {
        return;
    }
    firstIndex = self->scaled;
    if (self->selectedIndex < firstIndex) {
        return;
    }
    if (self->selectedIndex >= firstIndex + self->step) {
        return;
    }
    slot = self->selectedIndex % (u16)(self->step + 1);
    self->rows[slot]->selected = selected;
}

// slider: functions Slider_setPosition (0x020b9720), Slider_setPositionChecked (0x020b9740) and Slider_updateFlags
// (0x020b97d4), all matching. The slider keeps two children at +0x14 (see rect_pair.cpp for the child layout).

// Slider_updateFlags(self) (0x020b97d4, provisional name): does nothing when count is 1 or less; otherwise the bit
// unk_bit1 of child 0 is set when position <= 0 and that of child 1 when position + 1 >= count
void Slider_updateFlags(Slider *self) {
    SliderChild *child;

    if (self->count <= 1) {
        return;
    }
    child = self->children[0];
    child->flags.unk_bit1 = (self->position <= 0);
    child = self->children[1];
    child->flags.unk_bit1 = (self->position + 1 >= self->count);
}
