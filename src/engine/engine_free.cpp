#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/engine_free_api.h"
#include "sdk/os/os_arena.h"

// Frees a block to the system heap (no original name; was FreeToSystemHeap, the helper behind FreeIfSet_02005628).

void FreeToSystemHeap(void *block) {
    OS_FreeToHeap(0, -1, block);
}
