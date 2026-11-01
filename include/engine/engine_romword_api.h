#ifndef ENGINE_ENGINE_ROMWORD_API_H
#define ENGINE_ENGINE_ROMWORD_API_H

// Functions defined in src/engine/engine_romword*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Engine_ReadRomWord(void);
}

#endif
