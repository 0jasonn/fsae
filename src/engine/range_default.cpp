#include "engine/range_lookup.h"

// Provisional boundary names. The empty table has coincident start and end addresses.
extern "C" u8 RangeTableStart[];
extern "C" u8 RangeTableEnd[];

// Provisional name. Initialize the default bounds used by RangeLookup_Resolve.
s32 RangeLookup_SetDefaultBounds(RangeLookup *out, u32 key) {
    out->table = RangeTableStart;
    out->tableEnd = RangeTableEnd;
    return 1;
}
