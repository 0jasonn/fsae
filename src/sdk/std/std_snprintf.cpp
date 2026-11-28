#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/std/std_snprintf_api.h"

// func_0201dc94(dst, size, format, ...) (0x0201dc94; keeps its dsd name, rec_format.cpp calls it): variadic wrapper of
// STD_TVSNPrintf. The variadic arguments follow format in the caller's stack words.

s32 func_0201dc94(void *dst, s32 size, const u8 *format, ...) {
    return STD_TVSNPrintf((char *)dst, size, (const char *)format, (u8 *)(((u32)&format) & ~3) + 4);
}
