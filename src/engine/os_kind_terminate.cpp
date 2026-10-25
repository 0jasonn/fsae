#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Halfword flags at data_02129914: the first halfword is set for kind 0x10, the second for kind 0x20 before OS_Terminate.
typedef struct OsKindFlags {
    u16 first;
    u16 second;
} OsKindFlags;

extern OsKindFlags data_02129914;

extern "C" void OS_Terminate(void);
extern "C" void Os_TerminateByKind(u32 unused, u32 code);

// Os_TerminateByKind(unused, code) (0x02017008): takes the kind from bits 8 to 14 of code. Kind 0x10 sets the first flag and
// returns; kind 0x20 sets the second flag and terminates; any other kind terminates.
ARM void Os_TerminateByKind(u32 unused, u32 code) {
    u32 kind;

    kind = ((code & 0x7f00) << 8) >> 16;
    if (kind == 0x10) {
        data_02129914.first = 1;
        return;
    }
    if (kind == 0x20) {
        data_02129914.second = 1;
        OS_Terminate();
        return;
    }
    OS_Terminate();
}
