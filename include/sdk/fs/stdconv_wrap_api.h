#ifndef ENGINE_STDCONV_WRAP_API_H
#define ENGINE_STDCONV_WRAP_API_H

// Functions defined in src/engine/stdconv_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
u32 StdConv_SjisToUnicode(void *a, void *b, void *c, void *d, void *e);
u32 StdConv_UnicodeToSjis(void *a, void *b, void *c, void *d, void *e);
}

#endif
