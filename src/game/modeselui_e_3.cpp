#include "engine/functions.h"
#include "global.h"
#include "game/modeselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   modeSelUIView_viewWillApper (0x020a8ff0), modeSelUIView_leave (0x020a9048), func_020a9494 and func_020a94a4
//   (move(0) and move(1) wrappers, names kept because src/game/modeselui.cpp refers to them), modeSelUIView_update
//   (0x020aaaf8), modeSelUIView_vfunc2 (0x020aab7c)

// modeSelUIView::update() (0x020aaaf8): runs the handler of the current state (1 to 5) and stores the state it returns;
// a pending dialog number in unk_60 is shown first
ARM void modeSelUIView_update(ModeSelUIView *self) {
    s32 next;

    switch (self->unk_5c) {
    case 1:
        next = modeSelUIView_updateApper(self);
        break;
    case 2:
        next = modeSelUIView_updateMain(self);
        break;
    case 3:
        next = modeSelUIView_updateDisapper(self);
        break;
    case 4:
        next = modeSelUIView_updateCopy(self);
        break;
    case 5:
        next = modeSelUIView_updateRemove(self);
        break;
    }
    if (self->unk_60 != 0) {
        knife_title_dialogDisp(self->unk_60);
        self->unk_60 = 0;
    }
    if (next != 0) {
        self->unk_5d = 0;
        self->unk_5c = (u8)next;
    }
}

// modeSelUIView slot 2 (0x020aab7c): empty
ARM void modeSelUIView_vfunc2(void *self) {
}
