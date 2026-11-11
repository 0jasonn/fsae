#include "engine/functions.h"
#include "knife/message/tcl_layout.h"

// TclText_DrawBlockAligned (0x020c6b50): moves the origin along the cross direction to align the block within
// a box of the given height (end or centre), then draws the lines.
void TclText_DrawBlockAligned(TclLayoutDrawer *self, s32 x, s32 y, s32 width, s32 height, s32 palette, u32 flags, const u16 *text, TclLayoutStep step) {
    s32 offset;

    if (flags & TCL_ALIGN_BOX_V_END) {
        offset = height - TextBox_MeasureHeight(self->source, self->lineSpacing, text);
        x += offset * -step.dy;
        y += offset * step.dx;
    } else if (flags & TCL_ALIGN_BOX_V_CENTER) {
        offset = (height + 1) / 2 - (TextBox_MeasureHeight(self->source, self->lineSpacing, text) + 1) / 2;
        x += offset * -step.dy;
        y += offset * step.dx;
    }
    TclText_DrawLines(self, x, y, width, palette, flags, text, step);
}
