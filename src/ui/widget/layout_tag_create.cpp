#include "engine/functions.h"
#include "ui/widget/layout_tag.h"
#include "ui/widget/pane.h"

// The duplicate null checks preserve the original conditional constructor guard after the allocation-success branch.

s32 Window_createByTag(void *holder, u32 heap, void *spec, LayoutQuad q) {
    Pane *window;

    window = (Pane *)func_020c2c34(*(void **)holder, 0x28);
    if (window == NULL) {
        goto null;
    }
    if (window == NULL) {
        return (s32)window;
    }
    return (s32)func_020b5ba8(window, &heap, (const PaneSpec *)spec, &q);
null:
    return 0;
}

s32 TextBox_createByTag(void *holder, void *spec, LayoutQuad q) {
    void *textBox;

    textBox = func_020c2c34(*(void **)holder, 0x48);
    if (textBox == NULL) {
        goto null;
    }
    if (textBox == NULL) {
        return (s32)textBox;
    }
    return (s32)func_020b6bf8(textBox, spec, &q);
null:
    return 0;
}

s32 Picture_createByTag(void *holder, void *spec, LayoutQuad q) {
    Pane *picture;

    picture = (Pane *)func_020c2c34(*(void **)holder, 0x28);
    if (picture == NULL) {
        goto null;
    }
    if (picture == NULL) {
        return (s32)picture;
    }
    return (s32)func_020b5850(picture, (const PaneSpec *)spec, &q);
null:
    return 0;
}

s32 Pane_createByTag(void *holder, void *spec, LayoutQuad q) {
    Pane *pane;

    pane = (Pane *)func_020c2c34(*(void **)holder, 0x20);
    if (pane == NULL) {
        goto null;
    }
    if (pane == NULL) {
        return (s32)pane;
    }
    return (s32)Pane_initFromSpec(pane, (const PaneSpec *)spec, &q);
null:
    return 0;
}
