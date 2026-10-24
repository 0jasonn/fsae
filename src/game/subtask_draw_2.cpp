#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Subtask OAM helpers, 0x0209ceb8 to 0x0209cf98: OAM link priority, the OAM you entry, and the flag table access.

extern u8 data_0217d1b4[];

// subtask_draw_oam_you (0x0209ceb8)
ARM BOOL subtask_draw_oam_you(s32 x, s32 y, s32 palette, GXOamAttr *attr) {
    return subtask_draw_oam(x, y, 0x140, palette, (GXOamShape)0x80004000, attr);
}

// subtask_draw_oam_link (0x0209cee4)
ARM s32 subtask_draw_oam_link(s32 x, s32 y, NNSG2dCellAnimation *anim, GXOamAttr *attr, s32 c) {
    s32 i;
    s32 pos[2];
    s32 count;

    pos[0] = x;
    pos[1] = y;
    count = func_020c40a4(attr, 4, anim->cellRef, 0, pos, 0, 0);
    func_020c4064(anim, c);
    for (i = 0; i < count; i++) {
        attr[i].attr2 = (attr[i].attr2 & ~0xc00) | 0x400;
    }
    return count;
}

// subtask_redraw_text (0x0209cf68): Knife_Message_RedrawText with no argument list.
ARM void subtask_redraw_text(s32 index) {
    Knife_Message_RedrawText(index, 0);
}

// subtask_setFlag (0x0209cf78): stores a byte in the subtask flag table.
ARM void subtask_setFlag(u32 index, u8 value) {
    data_0217d1b4[index] = value;
}

// subtask_getFlag (0x0209cf88): reads a signed byte from the subtask flag table.
ARM s8 subtask_getFlag(u32 index) {
    return (s8)data_0217d1b4[index];
}
