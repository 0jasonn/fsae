#include "engine/functions.h"
#include "global.h"

// ResCursor_Seek (ResCursor_Seek, provisional name): moves the cursor to entry index of its table (table pointer at +0x1c,
// count at +0, entries of 8 bytes from +0xc). Sets the first position and, when the entry's halfword at +4 is not zero,
// the second one too. Returns 1 when the index is in range, otherwise 0.
extern "C" s32 ResCursor_Seek(u8 *cursor, u32 index);
ARM s32 ResCursor_Seek(u8 *cursor, u32 index) {
    u8 *table;
    u8 *entry;

    table = *(u8 **)(cursor + 0x1c);
    if (index < *(u16 *)table) {
        entry = *(u8 **)(table + 0xc) + (index << 3);
        *(u8 **)cursor = entry;
        if (*(u16 *)(entry + 4) != 0) {
            *(u8 **)(cursor + 4) = entry;
        }
        return 1;
    }
    return 0;
}

// ResRef_GetWord (ResRef_GetWord, provisional name): the word at the address held in +4.
extern "C" u32 ResRef_GetWord(u8 *ref);
ARM u32 ResRef_GetWord(u8 *ref) {
    return *(u32 *)*(u8 **)(ref + 4);
}
