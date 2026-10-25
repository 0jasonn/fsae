#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// lobby_ptrarray.cpp: function lobby_allocPtrArray (0x020b51c8), matching.

// lobby_allocPtrArray(owner, count) (0x020b51c8, provisional name): allocates count pointers (at least one) from the
// allocator of owner and clears them. Returns NULL when the allocation fails.
extern "C" void **lobby_allocPtrArray(void *owner, s32 count);
ARM void **lobby_allocPtrArray(void *owner, s32 count) {
    void **array;
    void **slot;
    u32 i;

    array = (void **)func_020c2c34(*(void **)owner, (count == 0 ? 1 : count) << 2);
    if (array == NULL) {
        return NULL;
    }
    for (i = 0; i < (u32)count; i++) {
        slot = &array[i];
        if (slot != NULL) {
            *slot = NULL;
        }
    }
    return array;
}
