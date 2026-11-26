#include "global.h"
#include "types.h"
#include "sdk/os/os_arena.h"

void *OS_GetArenaHi(s32 id) {
    return ((void **)0x02fffdc4)[id];
}

void *OS_GetArenaLo(s32 id) {
    return ((void **)0x02fffda0)[id];
}
