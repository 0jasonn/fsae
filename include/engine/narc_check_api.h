#ifndef ENGINE_NARC_CHECK_API_H
#define ENGINE_NARC_CHECK_API_H

// Functions defined in src/engine/narc_check*.cpp.

#include "engine/entity.h"

extern "C" {
s32 Narc_IsValidHeader(u8 *data);
}

#endif
