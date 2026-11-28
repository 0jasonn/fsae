#ifndef SDK_STD_STD_STRING_H
#define SDK_STD_STD_STRING_H

// TwlSDK STD string functions (std_string.c).
#include "types.h"

extern "C" {
char *STD_CopyString(char *dst, const char *src);
s32 STD_GetStringLength(const char *str);
s32 STD_CompareString(const char *a, const char *b);
s32 STD_CopyLString(char *dst, const char *src, s32 size);

// Not decompiled yet.
char *STD_SearchString(const char *haystack, const char *needle);
s32 STD_CompareNString(const char *a, const char *b, s32 count);
}

#endif
