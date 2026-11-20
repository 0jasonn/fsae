#ifndef UI_WIDGET_PANE_D_API_H
#define UI_WIDGET_PANE_D_API_H

// Functions defined in src/engine/pane_d*.cpp.

#include "engine/entity.h"

extern "C" {
void Pane_releaseItemNoop(void *item, void *heap);
}

#endif
