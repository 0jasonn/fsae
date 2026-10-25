#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"

// Functions in this file (plain names from the debug build, C linkage):
//   fileSelUIView_moveOut_wait (0x020a8178)

extern UIObject data_0217eb2c[]; // UI object table of the file select screen

// fileSelUIView::moveOut_wait() (0x020a8178): true once the first UI object has finished its move (ratio 0x1000)
extern "C" BOOL fileSelUIView_moveOut_wait(void *self);
ARM BOOL fileSelUIView_moveOut_wait(void *self) {
    return UIObject_getDurationRatio(data_0217eb2c) == 0x1000;
}
