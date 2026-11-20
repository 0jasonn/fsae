#ifndef ENGINE_TEXT_STREAM_API_H
#define ENGINE_TEXT_STREAM_API_H

// Character decoders shared by the message and UI text streams.

#include "engine/entity.h"

extern "C" {
u16 TextStream_ReadSjis(u8 *self);
u8 TextStream_ReadU8(u8 *self);
}

#endif
