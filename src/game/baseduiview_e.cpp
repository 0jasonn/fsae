#include "engine/functions.h"
#include "global.h"
#include "game/baseduiview.h"

// Functions in this file (no original names in the debug build, so plain C linkage):
//   groupCreateUIView_vfunc2 (0x020ac014): empty slot 2 of the groupCreateUIView vtable
//   basedUIView_leave (0x020ac018), basedUIView_enter (0x020ac01c), basedUIView_vfunc2 (0x020ac020),
//   basedUIView_vfunc1 (0x020ac024): the empty default slots of the basedUIView vtable at data_02124b40

extern "C" void groupCreateUIView_vfunc2(void *self);
extern "C" void basedUIView_leave(basedUIView *self);
extern "C" void basedUIView_enter(basedUIView *self);
extern "C" void basedUIView_vfunc2(basedUIView *self);
extern "C" void basedUIView_vfunc1(basedUIView *self);

// groupCreateUIView slot 2 (0x020ac014): empty
ARM void groupCreateUIView_vfunc2(void *self) {
}

// basedUIView default leave (0x020ac018): empty
ARM void basedUIView_leave(basedUIView *self) {
}

// basedUIView default enter (0x020ac01c): empty
ARM void basedUIView_enter(basedUIView *self) {
}

// basedUIView slot 2 (0x020ac020): empty
ARM void basedUIView_vfunc2(basedUIView *self) {
}

// basedUIView slot 1 (0x020ac024): empty
ARM void basedUIView_vfunc1(basedUIView *self) {
}
