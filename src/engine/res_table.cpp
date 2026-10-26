#include "engine/functions.h"
#include "global.h"

// ResTable_Relocate (ResTable_Relocate, provisional name): adds the table address to the table pointer at +4 and to each of
// the u32 offsets the table holds (count at +0).
extern "C" void ResTable_Relocate(u8 *table);
ARM void ResTable_Relocate(u8 *table) {
    u16 i;
    u32 *offsets;

    *(u32 *)(table + 4) += (u32)table;
    for (i = 0; i < *(u16 *)table; i++) {
        offsets = *(u32 **)(table + 4);
        offsets[i] = (u32)(table + offsets[i]);
    }
}
