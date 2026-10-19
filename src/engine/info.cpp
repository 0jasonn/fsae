#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   GetInfoAdrs

// Info table of 16 rows (one per area), each row with one pointer per kind
extern const u32 *data_02134968[];

// Pointer stored for (area, kind), or NULL when the area has no row
ARM const u8 *GetInfoAdrs(u8 area, u8 kind) {
    const u32 *row;

    row = (const u32 *)data_02134968[area];
    if (row == 0) {
        return 0;
    }
    return (const u8 *)row[kind];
}
