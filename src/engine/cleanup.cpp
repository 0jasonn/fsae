#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Object with a payload pointer at +0 and a cleanup callback at +8, called as callback(payload, -1).
typedef struct CleanupObj {
    void *payload;
    u32 unk_04;
    void (*cleanup)(void *, s32);
} CleanupObj;

// Entries of the init table at 0x020df56c (dsd name .p__sinit_020df208), ended by a zero entry.
extern "C" void Cleanup_Invoke(CleanupObj *self);
extern "C" void StaticInit_RunTable(void);

// Cleanup_Invoke(self) (0x0200c4a8): when both the payload and the callback are set, calls the callback with the payload
// and -1.
ARM void Cleanup_Invoke(CleanupObj *self) {
    void *payload;
    void (*cleanup)(void *, s32);

    payload = self->payload;
    if (payload != NULL) {
        cleanup = self->cleanup;
        if (cleanup != NULL) {
            cleanup(payload, -1);
        }
    }
}

// StaticInit_RunTable() (0x0200c4d0): calls each non-null function pointer of the table at 0x020df56c in order.
ARM void StaticInit_RunTable(void) {
    void (**entry)(void);

    entry = (void (**)(void))0x020df56c;
    while (entry != NULL && *entry != NULL) {
        (*entry)();
        entry++;
    }
}
