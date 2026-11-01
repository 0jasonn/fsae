#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/packed_reset_api.h"
#include "engine/packed_set_api.h"

// packed_reset_2: function Packed_deletingDtor (0x020b735c), matching. It follows Packed_resetSelf. The base destructor
// is Packed_noop (0x020b70fc), then the block is freed through operator delete.

// Packed_deletingDtor(self) (0x020b735c, provisional name): deleting destructor of the Packed class, returns self
void *Packed_deletingDtor(void *self) {
    Packed_noop(self);
    operator delete(self);
    return self;
}
