#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Frees the block if the pointer is set (dsd name FreeIfSet_02005628), through the heap helper func_02005610.
extern "C" void func_02005610(void *block);

extern "C" void FreeIfSet_02005628(void *block);

ARM void FreeIfSet_02005628(void *block) {
    if (block == NULL) {
        return;
    }
    func_02005610(block);
}
