#ifndef GAME_FILESELUI_API_H
#define GAME_FILESELUI_API_H

// Functions defined in src/game/fileselui*.cpp.

#include "engine/entity.h"

extern "C" {
BOOL fileSelUIView_moveOut_wait(void *self);
void fileSelUIView_viewDidDisapper(void *a);
}

#endif
