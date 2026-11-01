#ifndef ENGINE_TEXT_STREAM_API_H
#define ENGINE_TEXT_STREAM_API_H

// Functions defined in src/engine/text_stream*.cpp.

#include "engine/entity.h"

extern "C" {
u8 TextStream_ReadU8(u8 *self);
}

#endif
