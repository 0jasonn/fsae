#ifndef UI_WIDGET_LAYOUT_TAG_H
#define UI_WIDGET_LAYOUT_TAG_H

// Layout block dispatcher and the record constructors selected by its tag.

#include "engine/functions.h"
#include "types.h"

// Four-word block record passed by value to the layout helpers
typedef struct LayoutQuad {
    u32 word[4];
} LayoutQuad;

extern "C" {
s32 Pane_createByTag(void *holder, void *spec, LayoutQuad q);
s32 Picture_createByTag(void *holder, void *spec, LayoutQuad q);
s32 TextBox_createByTag(void *holder, void *spec, LayoutQuad q);
s32 Window_createByTag(void *holder, u32 heap, void *spec, LayoutQuad q);
s32 Layout_createByTag(void *unused, void *arg1, s32 tag, void *arg3, const LayoutQuad *q);
}

#endif
