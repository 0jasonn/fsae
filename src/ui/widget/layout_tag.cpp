#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/layout_tag.h"

// layout_tag: function Layout_createByTag (0x020b5318), provisional name Layout_createByTag.

// Dispatches on the four-character block tag. Windows also receive the heap stored in the holder's first word.
s32 Layout_createByTag(void *, void *holder, s32 tag, void *spec, const LayoutQuad *q) {
    switch (tag) {
    case 0x70616e31: // 'pan1'
        return Pane_createByTag(holder, spec, *q);
    case 0x70696331: // 'pic1'
        return Picture_createByTag(holder, spec, *q);
    case 0x74787431: // 'txt1'
        return TextBox_createByTag(holder, spec, *q);
    case 0x776e6431: // 'wnd1'
        return Window_createByTag(holder, *(u32 *)holder, spec, *q);
    }
    return 0;
}
