#ifndef WIP_E_FILESELUI_MOVE_H
#define WIP_E_FILESELUI_MOVE_H

// fileSelUIView::move(long) (0x020a7a60): the four move kinds (0 in, 1 out, 2 in after return, 3 out after return)
// and the wrappers in src/wip/E/fileselui_move.cpp.

#include "engine/functions.h"

extern "C" {
void fileSelUIView_move(void *self, s32 mode);
void fileSelUIView_moveIn(void *self);
void fileSelUIView_moveOut(void *self);
void fileSelUIView_moveOutReturn(void *self);
}

#endif
