#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Same test as FreeIfSet_02005628 (dsd name FreeIfSet_0200c748); calls it for a non-null pointer.
extern "C" void FreeIfSet_02005628(void *block);
extern "C" void FreeIfSet_0200c748(void *block); // plain name: the Knife sound and file units call it as C

ARM void FreeIfSet_0200c748(void *block) {
    if (block == NULL) {
        return;
    }
    FreeIfSet_02005628(block);
}
