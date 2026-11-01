#ifndef ENGINE_RECT_LIST_API_H
#define ENGINE_RECT_LIST_API_H

// Functions defined in src/engine/rect_list*.cpp.

#include "engine/entity.h"

extern "C" {
u16 *Group_allocU16Array(void *holder, s32 count);
u32 *Group_allocU32Array(void *holder, s32 count);
void Group_freeBlock(void *holder, void *block);
void Group_freeBlock2(void *holder, void *block);
void **RectObjList_allocPtrArray(void *holder, s32 count);
void RectObjList_freeBlock(void *holder, void *block);
}

#endif
