#include "knife/message/tcl_layout.h"

// Reader state is an opaque 32-bit cursor, as in TextBox_MeasureSegment.
extern "C" TclTextSize TextBox_MeasureBlock(TclTextSource *source, s32 charSpacing, s32 lineSpacing, u32 state) {
    TclTextSize size = {0, 0};
    s32 lineCount;
    s32 width;

    lineCount = 1;
    if (state != 0) {
        do {
            width = TextBox_MeasureSegment((u8 *)source, charSpacing, state, &state);
            if (width > size.width)
                size.width = width;
            lineCount++;
        } while (state != 0);
    }
    size.height = (lineCount - 1) * (lineSpacing + *(s8 *)((u8 *)source->data + 1)) - lineSpacing;
    return size;
}
