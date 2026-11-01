#ifndef ENGINE_RECT_ITEM_H
#define ENGINE_RECT_ITEM_H

#include "engine/entity.h"

// Item of a RectObjPair group (stride 0x18): three pointers, two heap blocks and a count
typedef struct RectItem {
    void *unk_00;      // 0x00
    void *unk_04;      // 0x04
    void *unk_08;      // 0x08
    void **block0c;   // 0x0c: pointer array, freed by RectItem_releaseBlocks
    void **block10;   // 0x10: pointer array, freed by RectItem_releaseBlocks
    u16 count;        // 0x14
} RectItem;

#endif
