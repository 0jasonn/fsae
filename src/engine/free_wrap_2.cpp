#include "engine/functions.h"
#include "global.h"
#include "types.h"

// operator delete (0x0200c748): frees a non-null block through FreeIfSet_02005628.
extern "C" void FreeIfSet_02005628(void *block);

ARM void operator delete(void *block) {
    if (block == NULL) {
        return;
    }
    FreeIfSet_02005628(block);
}
