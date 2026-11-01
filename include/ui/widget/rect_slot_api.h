#ifndef ENGINE_RECT_SLOT_API_H
#define ENGINE_RECT_SLOT_API_H

// Functions defined in src/engine/rect_slot*.cpp.

#include "engine/entity.h"

extern "C" {
s32 RectObjList_findHit2(void **items, s32 count, s16 *pos);
}

#endif
