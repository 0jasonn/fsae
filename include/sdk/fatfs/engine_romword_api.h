#ifndef SDK_FATFS_ENGINE_ROMWORD_API_H
#define SDK_FATFS_ENGINE_ROMWORD_API_H

// Functions defined in src/engine/engine_romword*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Engine_ReadRomWord(void);
}

#endif
