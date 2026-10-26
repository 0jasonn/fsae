#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// slider_ctrl: functions Ctrl_getSliderIndexA (0x020bac20), Ctrl_setSliderIndexA (0x020bac2c), Ctrl_getSliderIndexB
// (0x020bac58), Ctrl_setSliderIndexB (0x020bac64) and Ctrl_setFlagAndUpdate (0x020bac98), provisional names.

// Controller record: two sliders (pointers at +0x5c and +0x60), a pointer at +0x6c and the flag byte at +0xad
typedef struct SliderCtrl {
    u8 unk_00[0x5c];
    void *sliderA;     // 0x5c
    void *sliderB;     // 0x60
    u8 unk_64[8];
    void *unk_6c;      // 0x6c
    u8 unk_70[0x3d];
    u8 flag;           // 0xad
} SliderCtrl;

// Ctrl_getSliderIndexA(self) (0x020bac20, provisional name): the index of the slider at +0x5c
extern "C" s32 Ctrl_getSliderIndexA(SliderCtrl *self);
ARM s32 Ctrl_getSliderIndexA(SliderCtrl *self) {
    return ((s16 *)self->sliderA)[0x2a / 2];
}

// Ctrl_setSliderIndexA(self, value) (0x020bac2c, provisional name): sets the index of the slider at +0x5c, and when it
// changed, its position, then calls func_020bb148
extern "C" void Ctrl_setSliderIndexA(SliderCtrl *self, s32 value);
ARM void Ctrl_setSliderIndexA(SliderCtrl *self, s32 value) {
    if (Slider_setIndex(self->sliderA, value) != 0) {
        Slider_setPositionFromIndex(self->sliderA);
        func_020bb148(self);
    }
}

// Ctrl_getSliderIndexB(self) (0x020bac58, provisional name): the index of the slider at +0x60
extern "C" s32 Ctrl_getSliderIndexB(SliderCtrl *self);
ARM s32 Ctrl_getSliderIndexB(SliderCtrl *self) {
    return ((s16 *)self->sliderB)[0x2a / 2];
}

// Ctrl_setSliderIndexB(self, value) (0x020bac64, provisional name): sets the index of the slider at +0x60; when it
// changed and its position was set, calls func_020bb080
extern "C" void Ctrl_setSliderIndexB(SliderCtrl *self, s32 value);
ARM void Ctrl_setSliderIndexB(SliderCtrl *self, s32 value) {
    if (Slider_setIndex(self->sliderB, value) != 0) {
        if (Slider_setPositionFromIndex(self->sliderB) != 0) {
            func_020bb080(self);
        }
    }
}

// Ctrl_setFlagAndUpdate(self, value) (0x020bac98, provisional name): stores the low byte of value in the flag at +0xad,
// then calls RectSlot2_setFlag with the pointer at +0x6c and 1 when that byte is zero, otherwise 0
ARM void Ctrl_setFlagAndUpdate(void *selfv, s32 value) {
    SliderCtrl *self = (SliderCtrl *)selfv;
    self->flag = (u8)value;
    RectSlot2_setFlag(self->unk_6c, ((value & 0xff) == 0) ? 1 : 0);
}
