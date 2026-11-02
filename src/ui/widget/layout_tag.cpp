#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/layout_tag.h"

// layout_tag: function Layout_createByTag (0x020b5318), provisional name Layout_createByTag.

// Layout_createByTag(unused, arg1, tag, arg3, q) (0x020b5318, provisional name): dispatches on the four-character block
// tag: 'pan1', 'pic1' and 'txt1' call their helper with (arg1, arg3, *q), 'wnd1' calls func_020b5424 with arg1, the first
// word of arg1, arg3 and *q. Returns the helper's result, or 0 for an unknown tag.
s32 Layout_createByTag(void *unused, void *arg1, s32 tag, void *arg3, const LayoutQuad *q) {
    switch (tag) {
    case 0x70616e31: // 'pan1'
        return func_020b5524(arg1, arg3, *q);
    case 0x70696331: // 'pic1'
        return func_020b54d0(arg1, arg3, *q);
    case 0x74787431: // 'txt1'
        return func_020b547c(arg1, arg3, *q);
    case 0x776e6431: // 'wnd1'
        return func_020b5424(arg1, *(u32 *)arg1, arg3, *q);
    }
    return 0;
}
