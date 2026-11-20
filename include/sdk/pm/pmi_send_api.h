#ifndef ENGINE_PMI_SEND_API_H
#define ENGINE_PMI_SEND_API_H

// Functions defined in src/engine/pmi_send*.cpp.

#include "engine/entity.h"

extern "C" {
s32 PMi_StartSendBlock(u32 *words, s32 count, u32 a, u32 b, u32 c);
}

#endif
