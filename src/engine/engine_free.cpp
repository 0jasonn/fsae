#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Frees a block to the system heap (no original name; was FreeToSystemHeap, the helper behind FreeIfSet_02005628).
extern "C" void OS_FreeToHeap(u32 arena, u32 heap, void *block);
extern "C" void FreeToSystemHeap(void *block);

ARM void FreeToSystemHeap(void *block) {
    OS_FreeToHeap(0, (u32)-1, block);
}
