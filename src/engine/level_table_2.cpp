#include "engine/functions.h"
#include "global.h"
#include "types.h"

// level_table_2: function Level_deletingDtor (0x020b70e8), matching. It follows Level_noop, the empty destructor of the
// Level class, and frees the block through operator delete.

// Level_deletingDtor(self) (0x020b70e8, provisional name): deleting destructor of the Level class, returns self
extern "C" void *Level_deletingDtor(void *self);
ARM void *Level_deletingDtor(void *self) {
    operator delete(self);
    return self;
}
