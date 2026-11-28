#ifndef SDK_STD_STD_UNICODE_H
#define SDK_STD_STD_UNICODE_H

// TwlSDK STD Shift-JIS / UTF-16 conversion (std_unicode.c).
#include "types.h"

// Callback of the converters for a character that has no conversion: (output, output length, input, remaining input).
typedef s32 (*StdConvertCallback)(void *output, s32 *outputLength, const void *input, s32 *remaining);

// Conversion tables the converters read through (set up by the SDK start-up code).
extern u32 data_020dfbec;               // address of the UTF-16 to Shift-JIS table
extern u32 data_020dfbf0;               // address of the Shift-JIS (two byte characters) to UTF-16 table

// STDi_GetUnicodeConversionTable(u32 *unicodeToSjis, u32 *sjisToUnicode) is declared in engine/functions.h (stdconv_table_wrap
// calls it); it stores the two table addresses above.

#endif
