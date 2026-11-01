#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sdk_wrap.h"
#include "engine/stdconv_table_wrap_api.h"

// Tail call to STDi_GetUnicodeConversionTable.
u32 StdConv_GetUnicodeTable(u32 a, u32 b, u32 c, u32 d) {
    return STDi_GetUnicodeConversionTable(a, b, c, d);
}
