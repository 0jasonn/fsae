#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"

// slider: functions Slider_setPosition (0x020b9720), Slider_setPositionChecked (0x020b9740) and Slider_updateFlags
// (0x020b97d4), all matching. The slider keeps two children at +0x14 (see rect_pair.cpp for the child layout).

typedef struct SliderChild {
    void *vtable;          // 0x00
    u8 unk_04[0xc];
    RectFlagBits flags;    // 0x10
} SliderChild;

typedef struct Slider {
    u8 unk_00[0x14];
    SliderChild **children; // 0x14
    u8 unk_18[0xa];
    s16 scaled;             // 0x22: position * step
    u16 step;               // 0x24
    s16 position;           // 0x26
    u16 count;              // 0x28
    u8 unk_2a[0x10];
    s16 result;             // 0x3a
    u8 unk_3c;              // 0x3c
} Slider;

extern "C" void Slider_updateFlags(Slider *self);

// Slider_updateFlags(self) (0x020b97d4, provisional name): does nothing when count is 1 or less; otherwise the bit
// unk_bit1 of child 0 is set when position <= 0 and that of child 1 when position + 1 >= count
ARM void Slider_updateFlags(Slider *self) {
    SliderChild *child;

    if (self->count <= 1) {
        return;
    }
    child = self->children[0];
    child->flags.unk_bit1 = (self->position <= 0);
    child = self->children[1];
    child->flags.unk_bit1 = (self->position + 1 >= self->count);
}
