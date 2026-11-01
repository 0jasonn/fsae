#ifndef ENGINE_SLIDER_H
#define ENGINE_SLIDER_H

#include "engine/entity.h"

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

#endif
