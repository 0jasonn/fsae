#include "ui/widget/menu.h"

// Provisional scroll-state fields: viewport height at 0x0e, current offset at 0x1c,
// lower edge at 0x1e, range bounds at 0x20/0x22, and target offset at 0x24.
s32 func_020be518(void *object, u8 up, u8 down) {
    MenuList *state = (MenuList *)object;
    s32 extent;

    if (state->active != 0 && state->unk_20 < state->unk_22) {
        extent = Menu_CountItems(state);
        if (extent > state->unk_0e) {
            if (up != 0) {
                s32 target = state->unk_1c - 4;
                if (target <= 0) {
                    target = 0;
                }
                state->unk_24 = target;
            } else if (down != 0) {
                s32 max = state->unk_1e + 4;
                if (extent <= max) {
                    max = extent;
                }
                state->unk_24 = max - state->unk_0e;
            }
        }
    }
    return state->unk_1c != state->unk_24;
}
