#ifndef ENGINE_SLIDER_H
#define ENGINE_SLIDER_H

#include "engine/entity.h"

typedef struct SliderChild {
    void *vtable;          // 0x00
    u8 unk_04[0xc];
    RectFlagBits flags;    // 0x10
} SliderChild;

#endif
