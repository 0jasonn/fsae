#ifndef SDK_FATFS_STDCONV_TABLE_WRAP_API_H
#define SDK_FATFS_STDCONV_TABLE_WRAP_API_H

// Functions defined in src/engine/stdconv_table_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
void StdConv_GetUnicodeTable(u32 *table0, u32 *table1);
}

#endif
