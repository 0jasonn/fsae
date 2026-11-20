#ifndef UI_WIDGET_RECT_CREATE_2_H
#define UI_WIDGET_RECT_CREATE_2_H

// Heap-allocated rectangle objects: the create helpers that allocate a record from a holder's heap and run its
// initializer. The initializer prototypes are already in ui/widget/rect_create.h.

#include "types.h"
#include "ui/widget/rect_create.h"

extern "C" {
void *RectObjLink_create(void *holder);
void *RectSlot2_create(void *holder);
}

#endif
