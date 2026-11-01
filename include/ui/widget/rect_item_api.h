#ifndef ENGINE_RECT_ITEM_API_H
#define ENGINE_RECT_ITEM_API_H

// Functions defined in src/engine/rect_item*.cpp.

#include "engine/entity.h"

extern "C" {
void **RectItem_allocPtrArray(void *holder, s32 count);
void **RectItem_allocPtrArray2(void *holder, s32 count);
void RectItem_freeBlock(void *holder, void *block);
void RectItem_freeBlock2(void *holder, void *block);
}

#endif
