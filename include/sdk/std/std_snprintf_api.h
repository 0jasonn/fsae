#ifndef SDK_STD_STD_SNPRINTF_API_H
#define SDK_STD_STD_SNPRINTF_API_H

// TwlSDK STD formatted output (std_sprintf.c).
#include "types.h"

// Output cursor of STD_TVSNPrintf: bytes still free in the destination and the next write position (the position keeps
// advancing past the end so the total length is known).
typedef struct StdStringSink {
    u32 remaining; // 0x00
    char *cursor;  // 0x04
} StdStringSink;

extern "C" {
void string_put_char(StdStringSink *sink, char ch);
void string_fill_char(StdStringSink *sink, char ch, s32 count);
void string_put_string(StdStringSink *sink, const char *str, s32 count);
s32 STD_TSPrintf(char *dst, const char *fmt, ...);
s32 func_0201dc94(void *dst, s32 size, const u8 *format, ...); // STD_TSNPrintf (keeps its dsd name)

// Not decompiled yet.
s32 STD_TVSNPrintf(char *dst, u32 size, const char *fmt, void *args);
}

#endif
