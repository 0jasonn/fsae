#include "engine/functions.h"
#include "global.h"

// Functions in this file (plain names from the debug build, C linkage):
//   modeSelUIView_updateApper (0x020a9054)

extern "C" void func_020a9494(void *self);

// modeSelUIView::updateApper() (0x020a9054): runs func_020a9494 on the view and returns state 2
extern "C" s32 modeSelUIView_updateApper(void *self);
ARM s32 modeSelUIView_updateApper(void *self) {
    func_020a9494(self);
    return 2;
}
