#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// packed_reset: function Packed_resetSelf (0x020b7348), matching. It calls Packed_noop (0x020b70fc).

extern "C" void Packed_noop(void *self);
// Packed_resetSelf(self) (0x020b7348, provisional name): calls Packed_noop and returns self
extern "C" void *Packed_resetSelf(void *self);
ARM void *Packed_resetSelf(void *self) {
    Packed_noop(self);
    return self;
}
