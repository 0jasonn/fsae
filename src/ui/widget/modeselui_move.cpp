#include "engine/functions.h"
#include "ui/widget/uiobject.h"
#include "ui/modeselui_view.h"

// modeSelUIView_move (0x020a92e0): moves the three mode buttons and their labels in (step 0) or out (step 1). The
// order table holds the indices of the six UI objects, in pairs per button; data_020de838/data_020de848 are the two
// animation durations and data_020de8cc the x/y pairs of the button slots.

typedef struct MoveOrder {
    u8 ids[6];
} MoveOrder;

extern const MoveOrder data_020de790;
extern const s32 data_020de838;
extern const s32 data_020de848;
extern const s32 data_020de8cc[6];
extern UIObject data_0217eb2c[];

void modeSelUIView_move(ModeSelUIView *self, s32 step) {
    MoveOrder order = data_020de790;
    UIObject *a;
    s32 y;
    u32 i;
    s32 duration;
    u32 k;
    UIObject *b;
    s32 x;

    switch (step) {
    case 0: {
        s32 zero = 0;
        duration = data_020de838;

        for (i = 0; i < 3; i++) {
            b = &data_0217eb2c[order.ids[2 * i + 1]];
            a = &data_0217eb2c[order.ids[2 * i]];
            a->unk_02[1] = 1;
            b->unk_02[1] = 1;
            a->durationFP = zero;
            y = data_020de8cc[2 * i + 1];
            x = data_020de8cc[2 * i] << 12;
            a->pos.x = x;
            a->pos.y = (0x90 + y) << 12;
            b->durationFP = zero;
            b->pos.x = x;
            b->pos.y = (0x90 + y) << 12;
            UIObject_movePos(a, x, y << 12, duration, ANIMATION_CURVE_EASE_OUT);
            UIObject_movePos(b, x, y << 12, duration, ANIMATION_CURVE_EASE_OUT);
        }
        break;
    }
    case 1: {
        duration = data_020de848;
        for (k = 0; k < 3; k++) {
            y = (data_020de8cc[k * 2 + 1] + 0x90) << 12;
            b = &data_0217eb2c[order.ids[k * 2 + 1]];
            a = &data_0217eb2c[order.ids[k * 2]];
            x = data_020de8cc[2 * k] << 12;
            UIObject_movePos(a, x, y, duration, ANIMATION_CURVE_EASE_IN);
            UIObject_movePos(b, x, y, duration, ANIMATION_CURVE_EASE_IN);
        }
    }
    }
}
