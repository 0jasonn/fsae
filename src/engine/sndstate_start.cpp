#include "engine/functions.h"
#include "global.h"

extern "C" {
u8 *func_020c05ec(s32 index);
s32 func_020c186c(void *obj, u32 a, u32 b, u32 c, u8 *entry, s32 index);
}

// SndState_StartEntry: looks the index up through the state's +8 table (func_020c05ec) and, when there is an entry, passes
// three of its bytes and halfword and the entry itself to func_020c186c. Returns that result, or 0 when there is no entry.
extern "C" s32 SndState_StartEntry(void *obj, s32 index);
ARM s32 SndState_StartEntry(void *obj, s32 index) {
    u8 *entry;

    entry = func_020c05ec(index);
    if (entry == 0) {
        return 0;
    }
    return func_020c186c(obj, entry[0x9], *(u16 *)(entry + 0x4), entry[0x8], entry, index);
}
