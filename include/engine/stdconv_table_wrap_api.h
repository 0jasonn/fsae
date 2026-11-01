#ifndef ENGINE_STDCONV_TABLE_WRAP_API_H
#define ENGINE_STDCONV_TABLE_WRAP_API_H

// Functions defined in src/engine/stdconv_table_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
u32 StdConv_GetUnicodeTable(u32 a, u32 b, u32 c, u32 d);
}

#endif
