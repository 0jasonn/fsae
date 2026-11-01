#ifndef ENGINE_ENGINE_BYTES_API_H
#define ENGINE_ENGINE_BYTES_API_H

// Functions defined in src/engine/engine_bytes*.cpp.

#include "engine/entity.h"

extern "C" {
u8 *FindByteBackward(const u8 *buf, int value, u32 count);
}

#endif
