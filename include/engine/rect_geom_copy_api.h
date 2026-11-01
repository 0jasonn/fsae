#ifndef ENGINE_RECT_GEOM_COPY_API_H
#define ENGINE_RECT_GEOM_COPY_API_H

// Functions defined in src/engine/rect_geom_copy*.cpp.

#include "engine/entity.h"

extern "C" {
void RectObjList_setGeometryCopy(void *self, s16 *pos, s16 *size, s32 value, s32 a20, s32 a24);
}

#endif
