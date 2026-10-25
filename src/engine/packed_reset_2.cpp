#include "engine/functions.h"
#include "global.h"
#include "types.h"

// packed_reset_2: function Packed_deletingDtor (0x020b735c), matching. It follows Packed_resetSelf. The base destructor
// is Packed_noop (0x020b70fc), then the block is freed through operator delete.

extern "C" void Packed_noop(void *self);

// Packed_deletingDtor(self) (0x020b735c, provisional name): deleting destructor of the Packed class, returns self
extern "C" void *Packed_deletingDtor(void *self);
ARM void *Packed_deletingDtor(void *self) {
    Packed_noop(self);
    operator delete(self);
    return self;
}
