#include "engine/functions.h"
#include "global.h"

// ResTable_GetEntry (ResTable_GetEntry, provisional name): the entry at index when index is below the count at +0 (entries
// are 0x10 bytes from the base at +4), otherwise 0.
extern "C" u8 *ResTable_GetEntry(u8 *table, u32 index);
ARM u8 *ResTable_GetEntry(u8 *table, u32 index) {
    if (*(u16 *)table > index) {
        return *(u8 **)(table + 4) + (index << 4);
    }
    return 0;
}

// ResTable_GetEnd (ResTable_GetEnd, provisional name): the end of the entries. Entries are 0x10 bytes when bit 0 of the
// flags at +2 is set, 8 bytes otherwise.
extern "C" u8 *ResTable_GetEnd(u8 *table);
ARM u8 *ResTable_GetEnd(u8 *table) {
    u16 count;
    u8 *base;

    if (*(u16 *)(table + 2) & 1) {
        count = *(u16 *)table;
        base = *(u8 **)(table + 4);
        return base + (count << 4);
    }
    count = *(u16 *)table;
    base = *(u8 **)(table + 4);
    return base + (count << 3);
}

// ResTable_LookupFrom8 (ResTable_LookupFrom8, provisional name): looks up the table from the body at +8 through ResTable_Relocate.
extern "C" void *ResTable_Relocate(u8 *body);
extern "C" void *ResTable_LookupFrom8(u8 *table);
ARM void *ResTable_LookupFrom8(u8 *table) {
    return ResTable_Relocate(table + 8);
}
