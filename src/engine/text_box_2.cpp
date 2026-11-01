#include "engine/functions.h"
#include "global.h"
#include "engine/text_box_api.h"

// TextBox_MeasureWidth (provisional name): the widest segment of the state, measured with TextBox_MeasureSegment in turn
// (the out state is written back to the state each time) until the state is 0.
s32 TextBox_MeasureWidth(u8 *self, s32 base, u32 state, u32 unused) {
    s32 widest;
    s32 width;

    widest = 0;
    if (state != 0) {
        do {
            width = TextBox_MeasureSegment(self, base, state, &state);
            if (width > widest) {
                widest = width;
            }
        } while (state != 0);
    }
    return widest;
}
