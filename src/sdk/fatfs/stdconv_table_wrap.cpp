#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fatfs/stdconv_table_wrap_api.h"

// Tail call to STDi_GetUnicodeConversionTable.
void StdConv_GetUnicodeTable(u32 *table0, u32 *table1) {
    STDi_GetUnicodeConversionTable(table0, table1);
}
