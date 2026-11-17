#include "engine/functions.h"
#include "engine/os_thread.h"

// Provisional name. OS_CreateThread stores the returned ID at thread offset 0x6c.
u32 OSi_AllocateThreadId(void) {
    u32 id = data_0212991c.nextThreadId + 1;
    data_0212991c.nextThreadId = id;
    return id;
}
