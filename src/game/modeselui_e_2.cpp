#include "engine/functions.h"
#include "global.h"
#include "game/modeselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   modeSelUIView_viewWillApper (0x020a8ff0), modeSelUIView_leave (0x020a9048), func_020a9494 and func_020a94a4
//   (move(0) and move(1) wrappers, names kept because src/game/modeselui.cpp refers to them), modeSelUIView_update
//   (0x020aaaf8), modeSelUIView_vfunc2 (0x020aab7c)

// func_020a9494 (0x020a9494): modeSelUIView::move(0)
ARM void func_020a9494(void *self) {
    modeSelUIView_move((ModeSelUIView *)self, 0);
}

// func_020a94a4 (0x020a94a4): modeSelUIView::move(1)
ARM void func_020a94a4(void *self) {
    modeSelUIView_move((ModeSelUIView *)self, 1);
}
