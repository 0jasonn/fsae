#include "engine/functions.h"
#include "sdk/os/os_arena.h"
#include "sdk/os/device_flags_api.h"

// Arena set-up at boot.
void OS_InitArena(void) {
    s32 zero;
    s32 id;

    if (data_02129b94.initialized != 0) {
        return;
    }
    zero = 0;
    data_02129b94.initialized = 1;
    OS_SetArenaHi(zero, OS_GetInitArenaHi(zero));
    OS_SetArenaLo(zero, OS_GetInitArenaLo(zero));
    id = 2;
    OS_SetArenaLo(id, (void *)zero);
    OS_SetArenaHi(id, (void *)zero);
    id = 3;
    OS_SetArenaHi(id, OS_GetInitArenaHi(id));
    OS_SetArenaLo(id, OS_GetInitArenaLo(id));
    id = 4;
    OS_SetArenaHi(id, OS_GetInitArenaHi(id));
    OS_SetArenaLo(id, OS_GetInitArenaLo(id));
    id = 5;
    OS_SetArenaHi(id, OS_GetInitArenaHi(id));
    OS_SetArenaLo(id, OS_GetInitArenaLo(id));
    id = 6;
    OS_SetArenaHi(id, OS_GetInitArenaHi(id));
    OS_SetArenaLo(id, OS_GetInitArenaLo(id));
}

void OS_InitArenaEx(void) {
    s32 id;

    Device_InitFlags();
    id = 2;
    OS_SetArenaHi(id, OS_GetInitArenaHi(id));
    OS_SetArenaLo(id, OS_GetInitArenaLo(id));
    func_0218a5b8();
}
