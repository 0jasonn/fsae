#ifndef UI_WIDGET_SLIDER_H
#define UI_WIDGET_SLIDER_H

#include "engine/entity.h"

typedef struct SliderChild {
    void *vtable;          // 0x00
    u8 unk_04[0xc];
    RectFlagBits flags;    // 0x10
    u8 unk_11[0x29 - 0x11];
    u8 selected;          // 0x29: selection flag of a visible row
} SliderChild;

typedef struct Slider {
    u8 unk_00[0x14];
    SliderChild **children; // 0x14
    u8 unk_18[0xa];
    s16 scaled;             // 0x22: position * step
    volatile u16 step;      // 0x24: also the visible row count, read again for ring indexing
    s16 position;           // 0x26
    u16 count;              // 0x28
    s16 selectedIndex;      // 0x2a: -1 when no item is selected
    u8 unk_2c[4];
    SliderChild **rows;     // 0x30: visible children in the row ring
    u8 unk_34[6];
    s16 result;             // 0x3a
    u8 unk_3c;              // 0x3c
} Slider;

extern "C" {
void SliderRing_setSelectedChild(void *self, s32 selected);
}

#endif
