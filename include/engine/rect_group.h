#ifndef ENGINE_RECT_GROUP_H
#define ENGINE_RECT_GROUP_H

#include "engine/entity.h"

typedef struct RectGroup {
    u8 unk_00[0x14];
    void **items;  // 0x14
    u8 unk_18[0x10];
    u16 count;     // 0x28
    u8 unk_2a[6];
    void *block30; // 0x30
    void *block34; // 0x34
} RectGroup;

#endif
