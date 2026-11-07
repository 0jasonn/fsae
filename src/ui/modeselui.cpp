#include "engine/functions.h"
#include "global.h"
#include "ui/modeselui_view.h"
#include "ui/modeselui_api.h"
#include "ui/modeselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   modeSelUIView_viewWillApper (0x020a8ff0), modeSelUIView_leave (0x020a9048), func_020a9494 and func_020a94a4
//   (move(0) and move(1) wrappers, names kept because src/game/modeselui.cpp refers to them), modeSelUIView_update
//   (0x020aaaf8), modeSelUIView_vfunc2 (0x020aab7c)

// modeSelUIView::viewWillApper() (0x020a8ff0): pushes the child view when the lobby flag is set, otherwise resets the
// cursor and shows the mode select message
void modeSelUIView_viewWillApper(ModeSelUIView *self) {
    if (data_0217d23c[0xd0] != 0) {
        basedUIView_push_view((basedUIView *)data_0217e6f0, self->child);
    } else {
        self->unk_5c = 1;
        self->unk_5d = 0;
        self->unk_5b = 0;
        self->unk_60 = 0;
        knife_title_dialogDisp(0x835);
    }
}

// modeSelUIView::leave() (0x020a9048): the default leave, which only removes the title dialog
void modeSelUIView_leave(ModeSelUIView *self) {
    knife_title_dialogDelete();
}

// Functions in this file (plain names from the debug build, C linkage):
//   modeSelUIView_updateApper (0x020a9054)

extern "C" void func_020a9494(void *self);

// modeSelUIView::updateApper() (0x020a9054): runs func_020a9494 on the view and returns state 2
extern "C" s32 modeSelUIView_updateApper(void *self);
s32 modeSelUIView_updateApper(void *self) {
    func_020a9494(self);
    return 2;
}

// modeSelUIView::updateDisapper() (0x020a9064): state 0 starts the move out (move(1) and every UIObject slides to its
// off screen position), state 1 waits until the move is over, flags the objects, pops the view and shows the next
// message. Afterwards the oam entries of the three buttons are refreshed.
s32 modeSelUIView_updateDisapper(void *selfPtr) {
    ModeSelUIView *self = (ModeSelUIView *)selfPtr;
    ModeSelIndexTable oamIds = data_020de788;
    ModeSelIndexTable labelIds = data_020de7c0;
    u8 *labels;
    FileSelUIViewCtrl *ctrl;
    u32 i;
    s32 j;

    labels = labelIds.ids;
    switch (self->unk_5d) {
    case 0:
        func_020a94a4(self);
        UIObject_movePos(&data_0217fe14, data_020de85c.x << 12, data_020de85c.y << 12, data_020de848, ANIMATION_CURVE_EASE_IN);
        UIObject_movePos(&data_0217fe6c, data_020de85c.x << 12, data_020de85c.y << 12, data_020de848, ANIMATION_CURVE_EASE_IN);
        for (i = 0; i < 3; i++) {
            UIObject_movePos(&data_0217eb2c[(u8)i], data_020de8fc[i].x << 12, data_020de8fc[i].y << 12, data_020de848, ANIMATION_CURVE_EASE_IN);
            UIObject_movePos(&data_0217eb2c[labels[i * 2]], data_020de92c[i].x << 12, data_020de92c[i].y << 12, data_020de848, ANIMATION_CURVE_EASE_IN);
            UIObject_movePos(&data_0217eb2c[labels[i * 2 + 1]], data_020de92c[i].x << 12, data_020de92c[i].y << 12, data_020de848, ANIMATION_CURVE_EASE_IN);
        }
        self->unk_5d++;
        break;
    case 1:
        if (UIObject_getDurationRatio(&data_0217eef4) == 0x1000) {
            for (i = 0; i < 3; i++) {
                data_0217eb2c[(u8)i].unk_02[1] = 1;
                data_0217eb2c[labels[i * 2]].unk_02[1] = 1;
                data_0217eb2c[labels[i * 2 + 1]].unk_02[1] = 1;
            }
            *((u8 *)self->base.parent + 0x43) = 1;
            basedUIView_pop_view(self->base.parent);
            knife_title_dialogDisp(0x834);
        }
        break;
    }
    ctrl = (FileSelUIViewCtrl *)data_0217e6f0;
    for (j = 0; j < 3; j++) {
        if ((s8)self->unk_5b == j) {
            fileSelUIViewCtrl_addOamEntry_0ad964(ctrl, oamIds.ids[j * 2]);
        } else {
            fileSelUIViewCtrl_addOamEntry_0ad964(ctrl, oamIds.ids[j * 2 + 1]);
        }
    }
    return 0;
}
