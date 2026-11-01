#ifndef ENGINE_RECT_OBJ_H
#define ENGINE_RECT_OBJ_H

#include "engine/entity.h"

// The flag byte as bits: bit 0 freezes the bounds
typedef struct RectFlagBits {
    u8 frozen : 1;
    u8 rest : 7;
} RectFlagBits;

// RectObj record: offsets at +4 and +6 (the position), the size at +8 and +0xa, the bounds at +0xc and +0xe
typedef struct RectObj {
    void *vtable;      // 0x00
    s16 offsetX;       // 0x04
    s16 offsetY;       // 0x06
    s16 sizeX;         // 0x08
    s16 sizeY;         // 0x0a
    s16 boundX;        // 0x0c
    s16 boundY;        // 0x0e
    u8 flags;          // 0x10
} RectObj;

#endif
