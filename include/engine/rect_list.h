#ifndef ENGINE_RECT_LIST_H
#define ENGINE_RECT_LIST_H

#include "engine/entity.h"

// List of RectObj children: the rectangle (offset, size, bounds), flags at +0x10, the item array (or a value) at +0x14
// and the count at +0x18
typedef struct RectObjList {
    void *vtable;      // 0x00 (data_02126dc4)
    s16 offsetX;       // 0x04
    s16 offsetY;       // 0x06
    s16 sizeX;         // 0x08
    s16 sizeY;         // 0x0a
    s16 boundX;        // 0x0c
    s16 boundY;        // 0x0e
    u8 flags;          // 0x10: bit 0 freezes the bounds, bits 1 and 2 choose the kind in updateAndCall
    u8 unk_11[3];
    void *field14;     // 0x14: item array, or a value
    u16 count;         // 0x18
} RectObjList;

#endif
