#include "engine/functions.h"
#include "global.h"

// Functions in this file (plain names from the debug build, C linkage):
//   groupCreateUIView_leave (0x020ab6cc): empty leave slot 4

extern "C" void groupCreateUIView_leave(void *self);

// groupCreateUIView leave (0x020ab6cc): empty
ARM void groupCreateUIView_leave(void *self) {
}
