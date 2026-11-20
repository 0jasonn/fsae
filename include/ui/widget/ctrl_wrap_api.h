#ifndef UI_WIDGET_CTRL_WRAP_API_H
#define UI_WIDGET_CTRL_WRAP_API_H

// Functions defined in src/engine/ctrl_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Ctrl_getConst(void);
void Ctrl_updateSlotsA(void *self);
void Ctrl_waitVBlank(void);
}

#endif
