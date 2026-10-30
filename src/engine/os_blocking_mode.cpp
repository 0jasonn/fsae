#include "engine/functions.h"
#include "global.h"
#include "types.h"

// os_blocking_mode: function OS_GetPrintBlockingMode (0x020b07a4), keeps its symbol name.

// Minimal declaration of groupSelectUIView (no virtuals, so no vtable is emitted here)
class groupSelectUIView {
public:
    s32 getNumOfRoom(void) const;
};

// OS_GetPrintBlockingMode(self) (0x020b07a4): non-zero when groupSelectUIView::getNumOfRoom of self is non-zero
extern "C" s32 OS_GetPrintBlockingMode(void *self);
ARM s32 OS_GetPrintBlockingMode(void *self) {
    return ((groupSelectUIView *)self)->getNumOfRoom() != 0;
}
