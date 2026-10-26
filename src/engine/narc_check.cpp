#include "engine/functions.h"
#include "global.h"

// Narc_IsValidHeader (Narc_IsValidHeader, provisional name): 1 when the data starts with the NARC magic, the byte order mark
// 0xfffe at +4 and the version 0x100 at +6.
extern "C" s32 Narc_IsValidHeader(u8 *data);
ARM s32 Narc_IsValidHeader(u8 *data) {
    if (*(u32 *)data != 0x4352414e) {
        return 0;
    }
    if (*(u16 *)(data + 4) != 0xfffe) {
        return 0;
    }
    return *(u16 *)(data + 6) == 0x100;
}
