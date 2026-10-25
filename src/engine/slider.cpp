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

// Slider_setPosition(self, position) (0x020b9720, provisional name): stores the position, scales it by the step and
// updates the child flags
extern "C" void Slider_setPosition(Slider *self, s16 position);
ARM void Slider_setPosition(Slider *self, s16 position) {
    self->position = position;
    self->scaled = self->position * self->step;
    Slider_updateFlags(self);
}

// Slider_setPositionChecked(self, position) (0x020b9740, provisional name): returns 0 when the position is unchanged,
// otherwise sets it and stores the position times 0x17 in +0x3a, returning 1
extern "C" s32 Slider_setPositionChecked(Slider *self, s16 position);
ARM s32 Slider_setPositionChecked(Slider *self, s16 position) {
    if (self->position == position) {
        return 0;
    }
    Slider_setPosition(self, position);
    self->result = self->scaled * 0x17;
    return 1;
}
