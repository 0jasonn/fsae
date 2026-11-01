#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"
#include "engine/slider.h"

// slider: functions Slider_setPosition (0x020b9720), Slider_setPositionChecked (0x020b9740) and Slider_updateFlags
// (0x020b97d4), all matching. The slider keeps two children at +0x14 (see rect_pair.cpp for the child layout).

extern "C" void Slider_updateFlags(Slider *self);

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
