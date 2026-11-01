#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/engine_free_api.h"
#include "engine/free_wrap_api.h"

// Frees the block if the pointer is set (dsd name FreeIfSet_02005628), through the heap helper FreeToSystemHeap.

void FreeIfSet_02005628(void *block) {
    if (block == NULL) {
        return;
    }
    FreeToSystemHeap(block);
}
