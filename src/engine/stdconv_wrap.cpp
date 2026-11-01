#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/callees.h"
#include "engine/stdconv_wrap_api.h"

// Five-argument forwards to the string conversion helpers. The fifth argument is on the stack and is copied to the
// same slot for the callee, so the wrappers keep the full argument list.

u32 StdConv_SjisToUnicode(void *a, void *b, void *c, void *d, void *e) {
    return STD_ConvertStringSjisToUnicode(a, b, c, d, e);
}

u32 StdConv_UnicodeToSjis(void *a, void *b, void *c, void *d, void *e) {
    return STD_ConvertStringUnicodeToSjis(a, b, c, d, e);
}
