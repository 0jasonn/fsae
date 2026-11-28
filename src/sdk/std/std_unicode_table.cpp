#include "global.h"
#include "engine/functions.h"
#include "types.h"
#include "sdk/std/std_unicode.h"

void STDi_GetUnicodeConversionTable(u32 *unicodeToSjis, u32 *sjisToUnicode) {
    if (unicodeToSjis != NULL) {
        *unicodeToSjis = data_020dfbec;
    }
    if (sjisToUnicode != NULL) {
        *sjisToUnicode = data_020dfbf0;
    }
}
