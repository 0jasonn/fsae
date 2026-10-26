#include "engine/functions.h"
#include "global.h"
#include "game/modeselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   modeSelUIView_viewWillApper (0x020a8ff0), modeSelUIView_leave (0x020a9048), func_020a9494 and func_020a94a4
//   (move(0) and move(1) wrappers, names kept because src/game/modeselui.cpp refers to them), modeSelUIView_update
//   (0x020aaaf8), modeSelUIView_vfunc2 (0x020aab7c)

// modeSelUIView::viewWillApper() (0x020a8ff0): pushes the child view when the lobby flag is set, otherwise resets the
// cursor and shows the mode select message
ARM void modeSelUIView_viewWillApper(ModeSelUIView *self) {
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
ARM void modeSelUIView_leave(ModeSelUIView *self) {
    knife_title_dialogDelete();
}
