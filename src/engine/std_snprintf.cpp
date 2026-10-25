#include "engine/functions.h"
#include "global.h"
#include "types.h"

// STD_TVSNPrintf (0x0201dcbc): formats fmt with args into dst, at most size bytes.
extern "C" s32 STD_TVSNPrintf(u8 *dst, u32 size, const u8 *fmt, void *args);

// func_0201dc94(dst, size, format, ...) (0x0201dc94; keeps its dsd name, rec_format.cpp calls it): variadic wrapper of
// STD_TVSNPrintf. The variadic arguments follow format in the caller's stack words.
extern "C" s32 func_0201dc94(void *dst, s32 size, const u8 *format, ...);

ARM s32 func_0201dc94(void *dst, s32 size, const u8 *format, ...) {
    return STD_TVSNPrintf((u8 *)dst, size, format, (u8 *)(((u32)&format) & ~3) + 4);
}
